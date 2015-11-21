#include "Scene_Manager.h"

using namespace Managers;

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new Shader_Manager();
	shader_manager->CreateProgram("colorShader",
		"Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");

	shader_manager->CreateProgram("textureShader",
		"Shaders\\Texture_Vertex_Shader.glsl",
		"Shaders\\Texture_Fragment_Shader.glsl");

	shader_manager->CreateProgram("textureAlphaShader",
		"Shaders\\TextureAlpha_Vertex_Shader.glsl",
		"Shaders\\TextureAlpha_Fragment_Shader.glsl");

	models_manager = new Models_Manager();

	numberOfBlocksAlive = 60;

	Score = 0; 
	std::cout << "Score: " + std::to_string(Score) << std::endl;

	std::cout << "Loading physics..." << std::endl;

	float y = 0.125f;
	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 12.0f;
	float endAngle = 2.0f * pi - angleDelta;
	//float endAngle = pi/2.0f;
	float smallerRadius = 0.7f;
	int counter = 0;
	
	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 nevim = glm::vec4(0.5, 0.5, 0.5, 1);
	glm::vec4 pink = glm::vec4(1, 0, 1, 1);
	glm::vec4 azure = glm::vec4(0, 1, 1, 1);
	glm::vec4 color = yellow;
	int blockCounter = 0;
	for (float angle = 0.0f; angle < endAngle; angle += angleDelta)
	{
		counter++;
		//std::cout << counter << std::endl;

		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		//outer walls
		glm::vec3 a = glm::vec3(x, y, z);
		glm::vec3 b = glm::vec3(x2, y, z2);
		Block blocktemp = Block(a, b);

		//inner walls of well
		glm::vec3 aa = glm::vec3(xIn, y, zIn);
		glm::vec3 bb = glm::vec3(xIn2, y, zIn2);
		Block blocktemp2 = Block(aa, bb);
		blocktemp2.normal *= -1.0f;	//normal facing inside circle

		blockCounter += 2;//this is ugly, but time is short xD

		if (blockCounter <= 8)
			color = yellow;
		else if (blockCounter > 8 && blockCounter <= 16)
			color = green;
		else if (blockCounter > 16 && blockCounter <= 24)
			color = pink;
		else if (blockCounter > 24 && blockCounter <= 32)
			color = nevim;
		else if (blockCounter > 32 && blockCounter <= 40)
			color = blue;
		else if (blockCounter > 40 && blockCounter <= 48)
			color = azure;
		else
			color = red;

		//sides of bricks
		if (blockCounter % 8 == 0)//end
		{
			glm::vec3 aaa = glm::vec3(x2, y, z2);
			glm::vec3 bbb = glm::vec3(xIn2, y, zIn2);
			Block blocktempSide = Block(aaa, bbb);
			blocktempSide.color = color;
			blocks.push_back(blocktempSide);
			//models_manager->AddLine(aaa, bbb, color);
			//models_manager->AddLine(glm::vec3(blocktempSide.normal.x + blocktempSide.middle.x, y, blocktempSide.normal.y + blocktempSide.middle.z), blocktempSide.middle, color);
		}

		if (blockCounter % 8 == 2)//start
		{
			glm::vec3 aaa = glm::vec3(x, y, z);
			glm::vec3 bbb = glm::vec3(xIn, y, zIn);
			Block blocktempSide = Block(aaa, bbb);
			blocktempSide.color = color;
			blocktempSide.normal *= -1.0f;
			blocks.push_back(blocktempSide);
		}

		blocktemp.color = color;
		blocktemp2.color = color;

		blocks.push_back(blocktemp);
		blocks.push_back(blocktemp2);
	}

	bats = Bats(0);

	Ball::selectVelocity = true;
	Ball::enableMovement = false;

}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::notifyBeginFrame()
{
	//dealing with bats blocks
	blocks.resize(numberOfBlocksAlive);
	bats.Update();
	blocks.insert(blocks.end(), bats.blocksRotated.begin(), bats.blocksRotated.end());//append new blocks

	if (Ball::enableMovement){
		glm::vec2 ballPosition2D = glm::vec2(Ball::position.x, Ball::position.z);
		glm::vec2 ballVelocity2D = glm::vec2(Ball::velocity.x, Ball::velocity.z);

		float minimalDistance = 100.0f;
		Block closestBlock;
		std::string distancesStr = "";

		//std::cout << "--------------------------------------------" << std::endl;
		for (std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it)
		{
			Block block = *it;

			//triangle A,B,midd+normal - is ball in this triangle?
			//ball
			float x = ballPosition2D.x;
			float y = ballPosition2D.y;
			//A
			float x1 = block.A.x;
			float y1 = block.A.z;
			//B
			float x2 = block.B.x;
			float y2 = block.B.z;
			//midd+normal
			float x3 = block.middle.x + block.normal.x;
			float y3 = block.middle.z + block.normal.y;

			//barycentric solution
			// a = ((y 2  - y 3 )*(x - x 3 ) + (x 3  - x 2 )*(y - y 3 )) / ((y 2  - y 3 )*(x 1  - x 3 ) + (x 3 - x 2)*(y 1 - y 3))
			// b = ((y 3 - y 1)*(x - x 3) + (x 1 - x 3)*(y - y 3)) / ((y 2 - y 3)*(x 1 -x 3) + (x 3 - x 2)*(y 1 - y 3))
			// c = 1 - a - b

			float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			float c = 1.0f - a - b;

			if (0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1){

				/*
				float x0 = ballPosition2D.x;
				float y0 = ballPosition2D.y;

				float x1 = block.A.x;
				float y1 = block.A.z;

				float x2 = block.B.x;
				float y2 = block.B.z;

				float nahore = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1);
				float dole = sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
				float distance = abs(nahore / dole);
				distance -= Ball::radius;*/
				float distance = calculateBallBlockDistance(block);

				distancesStr += std::to_string(distance) + " ";

				if (distance < minimalDistance){
					minimalDistance = distance;
					closestBlock = block;
				}
			}
		}

		float minDistance = 0.01f;
		//if (minimalDistance <= 0.0f || minimalDistance < minDistance){
		if (minimalDistance <= 0.0f && minimalDistance < minDistance){

			std::cout << "HIT, distances: " << distancesStr << " ,min distance: " << minimalDistance << " ballposition2d " << ballPosition2D.x << ", " << ballPosition2D.y << std::endl;

			glm::vec3 vel = Ball::velocity;
			glm::vec3 normal = glm::vec3(closestBlock.normal.x, 0, closestBlock.normal.y);
			Ball::velocity = vel - 2 * glm::dot(vel, normal) * normal;

			Ball::Update();

			while (minimalDistance < minDistance){
				Ball::CorrectionUpdate(0.017f);
				minimalDistance = calculateBallBlockDistance(closestBlock);
			}

			std::cout << "Hit block no." << closestBlock.number << " which is " << Models_Manager::GetColorName(closestBlock.color) << " ax" << closestBlock.A.x << " az" << closestBlock.A.z << std::endl;
			EraseBlocksWithColor(closestBlock.color);

			Score += 100;
			std::cout << "Score: " + std::to_string(Score) << std::endl;

			if (numberOfBlocksAlive == 0){
				std::cout << "Winner!!!" << std::endl;
				Ball::enableMovement = false;
			}
			
		}
	}
		
	models_manager->Update();
	Camera::Update();
	Ball::Update();

	glm::vec3 normal = glm::vec3(0.0f - Ball::position.x, 0, 0.0f - Ball::position.z);
	float distanceFromCenter = glm::length(normal);

	if (distanceFromCenter + Ball::radius > 2.0f)
	{
		//std::cout << "reached outer wall of arena" << std::endl;

		Score -= 10;
		std::cout << "Score: " + std::to_string(Score) << std::endl;

		normal = glm::normalize(normal);
		normal = -1.0f * normal;

		glm::vec3 vel = Ball::velocity;
		Ball::velocity = vel - 2 * glm::dot(vel, normal) * normal;
	}
}

float Scene_Manager::calculateBallBlockDistance(const Block &block)
{
	float x0 = Ball::position.x;
	float y0 = Ball::position.z;

	float x1 = block.A.x;
	float y1 = block.A.z;

	float x2 = block.B.x;
	float y2 = block.B.z;

	float nahore = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1);
	float dole = sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
	float distance = abs(nahore / dole);

	distance -= Ball::radius;

	return distance;
}

void Scene_Manager::EraseBlocksWithColor(const glm::vec4 &color)
{
	if (color == glm::vec4(0, 0, 0, 0)){
		//std::cout << "Computer is refusing to erase this color. Sorry. Probably hit ball with bats..." << std::endl;
		return;
	}

	std::string closestBlockColorStr = Models_Manager::GetColorName(color);

	//std::cout << "Erasing all " << closestBlockColorStr << " bricks and blocks" << std::endl;

	int livesLeft = 0;
	for (std::vector<int>::size_type i = 0; i != blocks.size(); i++) 
	{
		Block block = blocks[i];

		if (block.color == color)
		{
			//std::cout << "reducing lives of block" << std::endl;
			livesLeft = block.lives - 1;
			block.lives--;
			blocks[i] = block;
		}

	}

	if (livesLeft == 3){
		std::string brickName = "brick" + closestBlockColorStr + "4";
		models_manager->DeleteModel(brickName);
	}
	if (livesLeft == 2){
		std::string brickName = "brick" + closestBlockColorStr + "3";
		models_manager->DeleteModel(brickName);
	}
	else if (livesLeft == 1){
		std::string brickName = "brick" + closestBlockColorStr + "2";
		models_manager->DeleteModel(brickName);
	}
	else if(livesLeft == 0){
		std::string brickName = "brick" + closestBlockColorStr;
		models_manager->DeleteModel(brickName);
	}

	std::vector<Block>::iterator iter;
	int counter = 0;
	for (iter = blocks.begin(); iter != blocks.end();) 
	{
		Block block = *iter;
		if (block.color == color && block.lives <= 0)
		{
			//std::cout << "erasing block" << std::endl;
			iter = blocks.erase(iter);
			counter++;
		}
		else
		{
			++iter;
		}
	}

	//std::cout << "Erased " << counter << " blocks" << Models_Manager::GetColorName(color) << " brick and blocks" << std::endl;

	numberOfBlocksAlive -= counter;
}



void Scene_Manager::notifyDisplayFrame()
{
	//TimeManager::CalculateFrameRate();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->Draw();
}

void Scene_Manager::notifyEndFrame()
{
	//nothing here for the moment
	//Ball::Update();
}

void Scene_Manager::notifyReshape(int width,
	int height,
	int previous_width,
	int previous_height)
{
	//nothing here for the moment 

}
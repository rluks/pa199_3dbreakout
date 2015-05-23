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
	models_manager = new Models_Manager();

	float y = 0.125f;
	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 8.0f;
	float endAngle = pi / 3.0f;
	float smallerRadius = 0.7f;
	int counter = 0;
	for (float angle = 0.0f; angle < endAngle; angle += angleDelta)
	{
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		glm::vec4 color;
		glm::vec4 red = glm::vec4(1, 0, 0, 1);
		glm::vec4 green = glm::vec4(0, 1, 0, 1);
		glm::vec4 blue = glm::vec4(0, 0, 1, 1);
		glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
		glm::vec4 nevim = glm::vec4(0.5, 0.5, 0.5, 1);
		glm::vec4 pink = glm::vec4(1, 0, 1, 1);

		if (counter == 0)
			color = yellow;
		else if (counter == 1)
			color = pink;
		else
			color = green;

		glm::vec3 a = glm::vec3(x, y, z);
		glm::vec3 b = glm::vec3(x2, y, z2);
		glm::vec3 middle = glm::vec3((x + x2)/2.0f, 0, (z + z2)/2.0f);

		Block blocktemp = Block(a, b);
		blocks.push_back(blocktemp);

		models_manager->AddLine(a, b, color);

		//block.normal.x = normalx + middle.x;
		//block.normal.y = normaly + middle.z;

		models_manager->AddLine(glm::vec3(blocktemp.normal.x+ middle.x, y, blocktemp.normal.y + middle.z), middle, color);

		counter++;
	}


}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::notifyBeginFrame()
{
	if (Ball::enableMovement){
		glm::vec2 ballPosition2D = glm::vec2(Ball::position.x, Ball::position.z);
		glm::vec2 ballVelocity2D = glm::vec2(Ball::velocity.x, Ball::velocity.z);

		std::vector<Block> closerSelection;
		for (std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it)
		{
			Block block = *it;
			glm::vec3 middle = glm::vec3((block.A.x + block.B.x) / 2.0f, 0, (block.A.z + block.B.z) / 2.0f);
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
			float x3 = middle.x + block.normal.x;
			float y3 = middle.z + block.normal.y;

			//barycentric solution
			// a = ((y 2  - y 3 )*(x - x 3 ) + (x 3  - x 2 )*(y - y 3 )) / ((y 2  - y 3 )*(x 1  - x 3 ) + (x 3 - x 2)*(y 1 - y 3))
			// b = ((y 3 - y 1)*(x - x 3) + (x 1 - x 3)*(y - y 3)) / ((y 2 - y 3)*(x 1 -x 3) + (x 3 - x 2)*(y 1 - y 3))
			// c = 1 - a - b

			float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			float c = 1.0f - a - b;

			if(0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c<= 1)
				closerSelection.push_back(block);

			/*float distancex = middle.x - ballPosition2D.x;
			float distancez = middle.z - ballPosition2D.y;
			float distanceFromMid = sqrt(distancex * distancex + distancez*distancez);

			if (distanceFromMid < 0.3f)
				closerSelection.push_back(block);*/
		}

		float minimalDistance = 100.0f;
		Block closestBlock;
		std::string distancesStr = "";
		for (std::vector<Block>::iterator it = closerSelection.begin(); it != closerSelection.end(); ++it)
		{
			Block block = *it;

			float x0 = ballPosition2D.x;
			float y0 = ballPosition2D.y;

			float x1 = block.A.x;
			float y1 = block.A.z;

			float x2 = block.B.x;
			float y2 = block.B.z;

			float nahore = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1);
			float dole = sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
			float distance = abs(nahore / dole);
			distance -= Ball::radius;

			//this should work great, but causes false collisions in the center, and no collisions where it supposed to...
			//distance = plane.normal · sphere.position 
			//distance = glm::dot(block.normal, ballPosition2D);


			//glm::vec3 middle = glm::vec3((block.A.x + block.B.x) / 2.0f, 0, (block.A.z + block.B.z) / 2.0f);
			//glm::vec2 fakeblocknormal = glm::vec2(block.normal.x + middle.x, block.normal.y + middle.z);
			//distance = glm::dot(fakeblocknormal, ballPosition2D);

			//std::cout << distance << std::endl;
			distancesStr += std::to_string(distance) + " ";

			if (distance < minimalDistance){
				minimalDistance = distance;
				closestBlock = block;
			}
		}


		float minDistance = 0.000005f;

		if (minimalDistance <= 0.0f || minimalDistance < minDistance){
			std::cout << "HIT, distances: " << distancesStr << std::endl;
			std::cout << "min   distance: " << minimalDistance << " ballposition2d " << ballPosition2D.x << ", " << ballPosition2D.y << std::endl;

			//Ball::velocity.x = 0.0f;
			//Ball::velocity.z = 0.0f;

			glm::vec3 vel = Ball::velocity;
			glm::vec3 normal = glm::vec3(closestBlock.normal.x, 0, closestBlock.normal.y);
			Ball::velocity = vel - 2 * glm::dot(vel, normal) * normal;
		}
	}
		
	models_manager->Update();
	Camera::Update();
	Ball::Update();
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
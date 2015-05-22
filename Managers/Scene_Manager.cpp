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

		block = Block(a, b);
		models_manager->AddLine(a, b, color);

		float dx = a.x - b.x;
		float dz = a.z - b.z;
		float normalx = -1*dz;
		float normaly = dx;

		block.normal.x = normalx + middle.x;
		block.normal.y = normaly + middle.z;

		models_manager->AddLine(glm::vec3(normalx+middle.x, y, normaly+middle.z), middle, color);

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
	glm::vec2 ballPosition2D = glm::vec2(Ball::position.x, Ball::position.z);
	glm::vec2 ballVelocity2D = glm::vec2(Ball::velocity.x, Ball::velocity.z);
	float x0 = ballPosition2D.x;
	float y0 = ballPosition2D.y;

	float x1 = block.A.x;
	float y1 = block.A.z;

	float x2 = block.B.x;
	float y2 = block.B.z;

	float nahore = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1);
	float dole = sqrt((y2-y1)*(y2-y1) +  (x2-x1)*(x2-x1));
	float distance = nahore / dole;
	distance -= Ball::radius;

	std::cout << "distance " <<  distance << " ballposition2d " << ballPosition2D.x << ", " << ballPosition2D.y << std::endl;

	float minDistance = 0.000005f;

	if (distance < minDistance){
		std::cout << "HIT" << std::endl;
		//Ball::velocity.x = 0.0f;
		//Ball::velocity.z = 0.0f;

		Ball::velocity.x *= -1.0f;
		Ball::velocity.z *= -1.0f;
	}
	//glm::vec2 reflected = block.normal * (block.normal * ballVelocity2D);
	//Ball::velocity -= glm::vec3(2*reflected.x, 0, 2*reflected.y);
		
	models_manager->Update();
	Camera::Update();
	Ball::Update();
}

void Scene_Manager::notifyDisplayFrame()
{
	TimeManager::CalculateFrameRate();

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
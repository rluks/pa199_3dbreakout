#include "Models_Manager.h"

using namespace Managers;
using namespace Rendering;

Models_Manager::Models_Manager()
{

	/*Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(Shader_Manager::GetShader("colorShader"));
	triangle->Create();
	gameModelList["triangle"] = triangle;*/

	/*Models::Quad* quad = new Models::Quad();
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;*/

	/*Models::Cube* cube = new Models::Cube();
	cube->SetProgram(Shader_Manager::GetShader("colorShader"));
	cube->Create();
	gameModelList["cube"] = cube;*/

	Models::Sphere* sphere = new Models::Sphere();
	sphere->SetProgram(Shader_Manager::GetShader("textureShader"));
	sphere->Create();
	gameModelList["sphere"] = sphere;

	Models::Circle* circle = new Models::Circle();
	circle->SetProgram(Shader_Manager::GetShader("textureShader"));
	circle->Create();
	gameModelList["circle"] = circle;

	/*Models::Brick* brick = new Models::Brick(0.0f);
	brick->SetProgram(Shader_Manager::GetShader("colorShader"));
	brick->Create();
	gameModelList["brick"] = brick;*/

	/*float y = 0.125f;
	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 8.0f;
	float endAngle = pi / 3.0f;
	float smallerRadius = 0.7f;
	for (float angle = 0.0f; angle < endAngle; angle += angleDelta)
	{
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		glm::vec3 a = glm::vec3(x, y, z);
		glm::vec3 b = glm::vec3(x2, y, z2);

		glm::vec4 pink = glm::vec4(1, 0, 1, 1);

		std::string mapKey = "line" + std::to_string(angle);
		Models::Line* line = new Models::Line(a, b, pink);
		line->SetProgram(Shader_Manager::GetShader("colorShader"));
		line->Create();
		gameModelList[mapKey] = line;
	}*/

	for (float angle = 0.0f; angle < 300.0f; angle += 67.5f)
	{
		std::string mapKey = "brick" + std::to_string(angle);

		Models::Brick* temp = new Models::Brick(angle);
		temp->SetProgram(Shader_Manager::GetShader("textureShader"));
		temp->Create();
		gameModelList[mapKey] = temp;

		/*Models::BrickCollider* brickCollider = new Models::BrickCollider(angle);
		brickCollider->SetProgram(Shader_Manager::GetShader("colorShader"));
		brickCollider->Create();
		gameModelList[mapKey + "Collider"] = brickCollider;*/
	}

	Models::Bat* bat = new Models::Bat(0.0f);
	bat->SetProgram(Shader_Manager::GetShader("textureShader"));
	bat->Create();
	gameModelList["bat"] = bat;

	Models::Ray* ray = new Models::Ray();
	ray->SetProgram(Shader_Manager::GetShader("colorShader"));
	ray->Create();
	gameModelList["ray"] = ray;



}

Models_Manager::~Models_Manager()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void Models_Manager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& Models_Manager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void Models_Manager::AddLine(glm::vec3 a, glm::vec3 b, const glm::vec4 &color)
{
	std::string mapKey = "line" + std::to_string(gameModelList.size());

	Models::Line* line = new Models::Line(a, b, color);
	line->SetProgram(Shader_Manager::GetShader("colorShader"));
	line->Create();
	gameModelList[mapKey] = line;
}

void Models_Manager::Update()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		/*
		if (InputManager::switchShaders)
		{
			GLuint program = Shader_Manager::GetShader("colorShader");
			model.second->SetProgram(program);
		}
		else
		{
			GLuint program = Shader_Manager::GetShader("textureShader");
			model.second->SetProgram(program);
		}*/

		model.second->Update();
	}

	/*
	//Haha, this caused drops in FPS from 60fps to only 10fps.. creating circle every update, foolish...
	
	Models::Circle* circle = new Models::Circle();
	circle->SetProgram(Shader_Manager::GetShader("textureShader"));
	circle->Create();
	gameModelList["circle"] = circle;*/
}

void Models_Manager::Draw()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}
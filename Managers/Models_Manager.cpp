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
	sphere->SetProgram(Shader_Manager::GetShader("colorShader"));
	sphere->Create();
	gameModelList["sphere"] = sphere;

	Models::Circle* circle = new Models::Circle();
	circle->SetProgram(Shader_Manager::GetShader("colorShader"));
	circle->Create();
	gameModelList["circle"] = circle;

	/*Models::Brick* brick = new Models::Brick(0.0f);
	brick->SetProgram(Shader_Manager::GetShader("colorShader"));
	brick->Create();
	gameModelList["brick"] = brick;*/

	for (int angle = 0; angle < 360; angle += 60)
	{
		std::string mapKey = "brick" + std::to_string(angle);
		Models::Brick* temp = new Models::Brick((float)angle);
		temp->SetProgram(Shader_Manager::GetShader("colorShader"));
		temp->Create();
		gameModelList[mapKey] = temp;
	}

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

void Models_Manager::Update()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Update();
	}
}

void Models_Manager::Draw()
{
	//auto -it's a map iterator
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}
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

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 grey = glm::vec4(0.5, 0.5, 0.5, 1);
	glm::vec4 pink = glm::vec4(1, 0, 1, 1);
	glm::vec4 azure = glm::vec4(0, 1, 1, 1);
	glm::vec4 color = yellow;
	int counter = 0;
	for (float angle = 0.0f; angle < 360.0f; angle += 60.0f)
	{
		switch (counter){
			case 0:
				color = yellow;
				break;
			case 1:
				color = azure;
				break;
			case 2:
				color = blue;
				break;
			case 3:
				color = grey;
				break;
			case 4:
				color = pink;
				break;
			case 5:
				color = green;
				break;
			default:
				std::cout << "wrong color" << std::endl;
				color = glm::vec4(0.1, 0.3, 0.6, 1.0);
				break;

		}

		std::string mapKey = "brick" + GetColorName(color);

		float ypsilon = 0.0f;
		Models::Brick* temp = new Models::Brick(angle, color, ypsilon);
		temp->SetProgram(Shader_Manager::GetShader("textureAlphaShader"));
		temp->Create();
		gameModelList[mapKey] = temp;

		mapKey = "brick" + GetColorName(color) + "2";
		ypsilon += 0.2f;

		Models::Brick* temp2 = new Models::Brick(angle, color, ypsilon);
		temp2->SetProgram(Shader_Manager::GetShader("textureAlphaShader"));
		temp2->Create();
		gameModelList[mapKey] = temp2;

		mapKey = "brick" + GetColorName(color) + "3";
		ypsilon += 0.2f;

		Models::Brick* temp3 = new Models::Brick(angle, color, ypsilon);
		temp3->SetProgram(Shader_Manager::GetShader("textureAlphaShader"));
		temp3->Create();
		gameModelList[mapKey] = temp3;

		mapKey = "brick" + GetColorName(color) + "4";
		ypsilon += 0.2f;

		Models::Brick* temp4 = new Models::Brick(angle, color, ypsilon);
		temp4->SetProgram(Shader_Manager::GetShader("textureAlphaShader"));
		temp4->Create();
		gameModelList[mapKey] = temp4;

		/*Models::BrickCollider* brickCollider = new Models::BrickCollider(angle);
		brickCollider->SetProgram(Shader_Manager::GetShader("colorShader"));
		brickCollider->Create();
		gameModelList[mapKey + "Collider"] = brickCollider;*/
		counter++;
	}

	Models::Bat* bat = new Models::Bat(0.0f);
	bat->SetProgram(Shader_Manager::GetShader("textureAlphaShader"));
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
	if (gameModelList.find(gameModelName) == gameModelList.end()){
		std::cout << "Unable to find desired model" << std::endl;
		return;
	}

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
	//std::cout << "mapkey" << mapKey << std::endl;

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

std::string Models_Manager::GetColorName(const glm::vec4 &color)
{
	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 grey = glm::vec4(0.5, 0.5, 0.5, 1);
	glm::vec4 pink = glm::vec4(1, 0, 1, 1);
	glm::vec4 azure = glm::vec4(0, 1, 1, 1);

	if (color == red)
		return "red";
	else if (color == green)
		return "green";
	else if (color == blue)
		return "blue";
	else if (color == yellow)
		return "yellow";
	else if (color == grey)
		return "grey";
	else if (color == pink)
		return "pink";
	else if (color == azure)
		return "azure";
	else{
		//std::string colorStr = std::to_string(color.a) + "," + std::to_string(color.g) + "," + std::to_string(color.b);
		std::string colorStr = "UNKNOWN";
		return colorStr;
	}

}

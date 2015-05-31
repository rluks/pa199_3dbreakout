#include "Model.h"

using namespace Rendering;
using namespace Models;

tdogl::Bitmap Model::ballTexture = tdogl::Bitmap::bitmapFromFile("Textures/ball.png");
tdogl::Bitmap Model::batTexture = tdogl::Bitmap::bitmapFromFile("Textures/bat.png");
tdogl::Bitmap Model::brickTexture = tdogl::Bitmap::bitmapFromFile("Textures/brick.png");
tdogl::Bitmap Model::grassTexture = tdogl::Bitmap::bitmapFromFile("Textures/grass.png");

Model::Model()
{
	verticesSize = 0;
	gTexture = NULL;
}

Model::~Model()
{
	Destroy();
}

glm::vec3 Model::getNorm(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
	glm::vec3 normal = glm::cross(B - A, C - A);

	normal = glm::normalize(normal);

	return normal;
}

void Model::Draw()
{
	//this will be again overridden
}

void Model::Update()
{
	//this will be again overridden
}

void Model::SetProgram(GLuint program)
{
	this->program = program;

	camera = glGetUniformLocation(program, "camera");
	projection = glGetUniformLocation(program, "projection");
	model = glGetUniformLocation(program, "model");
	texture2d = glGetUniformLocation(program, "tex");

	lightColor = glGetUniformLocation(program, "lightColor");
	lightPosition = glGetUniformLocation(program, "lightPosition");
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}


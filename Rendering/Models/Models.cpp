#include "Model.h"

using namespace Rendering;
using namespace Models;

glm::mat4 Model::projectionMatrix = glm::perspective(glm::radians(35.0f), 800.0f / 600.0f, 0.1f, 10.0f);
glm::vec3 Model::topView = glm::vec3(0, 6, 0.1);
glm::vec3 Model::perspectiveView = glm::vec3(0, 4, 4);
glm::vec3 Model::selectedView;

Model::Model()
{
	verticesSize = 0;
	gTexture = NULL;
	selectedView = perspectiveView;
}

Model::~Model()
{
	Destroy();
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
#include "Triangle.h"
using namespace Rendering;
using namespace Models;

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
	//is going to be deleted in Models.cpp (inheritance)
}

void Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec2 zeros = glm::vec2(0, 0);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), red, zeros));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), red, zeros));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0), glm::vec4(0, 0, 1, 1), zeros));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),(void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Triangle::Update()
{

}

void Triangle::Draw()
{
	glUseProgram(program);

	GLuint camera = glGetUniformLocation(program, "camera");
	GLuint projection = glGetUniformLocation(program, "projection");
	GLuint model = glGetUniformLocation(program, "model");

	//eye - position of the camera's viewpoint, center - where are you looking, up = up is Y+
	glm::mat4 cameraMatrix = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 10.0f);

	glm::mat4 identityMx = glm::mat4(	glm::vec4(1, 0, 0, 0),
										glm::vec4(0, 1, 0, 0),
										glm::vec4(0, 0, 1, 0),
										glm::vec4(0, 0, 0, 1));

	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(identityMx));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
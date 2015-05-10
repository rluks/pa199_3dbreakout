#include "Cube.h"
using namespace Rendering;
using namespace Models;

Cube::Cube()
{}

Cube::~Cube()
{}

void Cube::Create()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);

	//vertices.push_back(VertexFormat(glm::vec3(-0.5, 0.5, 0.0), red));
	//vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.5, 0.0), green)); 
	//vertices.push_back(VertexFormat(glm::vec3(0.5, 0.5, 0.0), blue)); 
	//vertices.push_back(VertexFormat(glm::vec3(0.5, -0.5, 0.0), red));

		// bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, 1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, 1.0f), blue));

		// top
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, -1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, -1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, 1.0f), green));

		// front
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, 1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, 1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, 1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, 1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, 1.0f), red));

		// back
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, -1.0f), red));

		// left
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, -1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, 1.0f), green));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, 1.0f, -1.0f), blue));

		// right
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, 1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, -1.0f), red));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, -1.0f, 1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, -1.0f), blue));
	vertices.push_back(VertexFormat(glm::vec3(1.0f, 1.0f, 1.0f), blue));


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*6*6, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),(void*)(offsetof(VertexFormat, VertexFormat::color)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Cube::Update()
{
	//nothing here for the moment
}

void Cube::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
}
#include "BrickCollider.h"

using namespace Rendering;
using namespace Models;

BrickCollider::BrickCollider(float pAngle)
{
	Angle = pAngle;
}

BrickCollider::~BrickCollider()
{}

void BrickCollider::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = brickTexture;
	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 nevim = glm::vec4(0.5, 0.5, 0.5, 1);

	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec2 zeros = glm::vec2(0, 0);

	float y = 0.2f;
	
	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 8.0f;
	float endAngle = pi/3.0f;
	float smallerRadius = 0.7f;
	for (float angle = 0.0f; angle < endAngle; angle += angleDelta)
	{
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		glm::vec2 zeros = glm::vec2(0, 0);
		glm::vec2 originTex = glm::vec2(0.5, 0.5);

		glm::vec2 texCoord = glm::vec2(x / 2 + 0.5, z / 2 + 0.5);
		glm::vec2 texCoord2 = glm::vec2(x2 / 2 + 0.5, z2 / 2 + 0.5);
		glm::vec2 texCoordIn = glm::vec2(xIn / 2 + 0.5, zIn / 2 + 0.5);
		glm::vec2 texCoordIn2 = glm::vec2(xIn2 / 2 + 0.5, zIn2 / 2 + 0.5);

		//outer wall
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, glm::vec2(0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), blue, glm::vec2(0, 0)));

		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, glm::vec2(0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, glm::vec2(1, 1)));

		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), blue, glm::vec2(0, 0)));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0)));

		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, glm::vec2(1, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0)));

		//inner wall
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1)));//vertical
		vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), blue, glm::vec2(0, 0)));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1)));//horizontal top
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, glm::vec2(1, 1)));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), blue, glm::vec2(0, 0)));//horizontal bottom
		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), blue, glm::vec2(1, 0)));

		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, glm::vec2(1, 1)));//vertical
		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), blue, glm::vec2(1, 0)));
	}

	float angle = 0.0f;

	{//one end wall
	
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), yellow, glm::vec2(0, 0)));
		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), yellow, glm::vec2(1, 0)));

		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), yellow, glm::vec2(0, 0)));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), yellow, glm::vec2(0, 1)));

		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), yellow, glm::vec2(0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), yellow, glm::vec2(1, 1)));

		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), yellow, glm::vec2(1, 0)));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), yellow, glm::vec2(1, 1)));

	}

	angle += pi / 8.0f;
	angle += pi / 8.0f;

	{//second end wall
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), green, glm::vec2(0, 0)));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), green, glm::vec2(1, 0)));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), green, glm::vec2(0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), green, glm::vec2(1, 1)));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), green, glm::vec2(0, 1)));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), green, glm::vec2(0, 0)));

		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), green, glm::vec2(1, 1)));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), green, glm::vec2(1, 0)));
	}

	verticesSize = vertices.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verticesSize, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

	glm::mat4 identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));

	rotated = glm::rotate(identityMx, glm::radians(Angle), glm::vec3(0.0f, 1.0f, 0.0f));

}

void BrickCollider::Update()
{
	cameraMatrixCopy = Camera::cameraMatrix;
}

void BrickCollider::Draw()
{
	glUseProgram(program);	

	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrixCopy));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Camera::projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(rotated));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture->object());
	glUniform1i(texture2d, 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, verticesSize);

}
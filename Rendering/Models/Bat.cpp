#include "Bat.h"

using namespace Rendering;
using namespace Models;

Bat::Bat(float pAngle)
{
	angle = pAngle;
	dxB = 0.0f;
	angleOffset = 0.0f;
}

Bat::~Bat()
{}

void Bat::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = Model::batTexture;
	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	generateBatVertices(0.0f, vertices);
	generateBatVertices(120.0f, vertices);
	generateBatVertices(240.0f, vertices);

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

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

	identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));
}

void Bat::generateBatVertices(float startAngle, std::vector<VertexFormat> &vertices)
{
	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 nevim = glm::vec4(0.5, 0.5, 0.5, 1);

	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec2 zeros = glm::vec2(0, 0);

	float y = 0.2f;

	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 16.0f;
	startAngle = glm::radians(startAngle);
	float endAngle = pi / 6.0f;
	float smallerRadius = 1.7f;
	float radius = 2.0f;
	int counter = 0;
	int lastIteration = 3;

	for (float angle = startAngle; angle < startAngle+endAngle; angle += angleDelta)
	{
		counter++;

		float x = radius * cos(angle);
		float z = radius * sin(angle);

		float x2 = radius * cos(angle + angleDelta);
		float z2 = radius * sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		glm::vec2 zeros = glm::vec2(0, 0);
		glm::vec2 originTex = glm::vec2(0.5, 0.5);

		glm::vec2 texCoord = glm::vec2(x / 4 + 0.5, z / 4 + 0.5);
		glm::vec2 texCoord2 = glm::vec2(x2 / 4 + 0.5, z2 / 4 + 0.5);
		glm::vec2 texCoordIn = glm::vec2(xIn / 4 + 0.5, zIn / 4 + 0.5);
		glm::vec2 texCoordIn2 = glm::vec2(xIn2 / 4 + 0.5, zIn2 / 4 + 0.5);

		glm::vec3 upNormal = glm::vec3(0, 1, 0);

		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, texCoord, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, texCoord2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, texCoordIn, upNormal));

		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, texCoord2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, texCoordIn2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, texCoordIn, upNormal));

		//outer wall
		glm::vec3 outerWallNormal = Model::getNorm(glm::vec3(x, y, z), glm::vec3(x, 0, z), glm::vec3(x2, 0, z2));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, glm::vec2(0, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, 0, z), blue, glm::vec2(0, 0), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, glm::vec2(0, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, glm::vec2(1, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0), outerWallNormal));

		//inner wall
		glm::vec3 innerWallNormal = Model::getNorm(glm::vec3(xIn2, y, zIn2), glm::vec3(xIn2, 0, zIn2), glm::vec3(xIn, 0, zIn));
		innerWallNormal *= -1.0f;
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), blue, glm::vec2(0, 0), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), blue, glm::vec2(1, 0), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, glm::vec2(1, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), blue, glm::vec2(1, 0), innerWallNormal));

		if (angle == startAngle)//vertical wall
		{
			glm::vec3 verticalWallNormal = Model::getNorm(glm::vec3(xIn, 0, zIn), glm::vec3(x, 0, z), glm::vec3(xIn, y, zIn));
			verticalWallNormal *= -1.0f;
			vertices.push_back(VertexFormat(glm::vec3(xIn, 0, zIn), blue, glm::vec2(0, 0), verticalWallNormal));
			vertices.push_back(VertexFormat(glm::vec3(x, 0, z), blue, glm::vec2(1, 0), verticalWallNormal));
			vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, glm::vec2(0, 1), verticalWallNormal));

			vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), blue, glm::vec2(0, 1), verticalWallNormal));
			vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, glm::vec2(1, 1), verticalWallNormal));
			vertices.push_back(VertexFormat(glm::vec3(x, 0, z), blue, glm::vec2(1, 0), verticalWallNormal));

		}
		else if (counter == lastIteration)
		{
			glm::vec3 verticalWallNormal2 = Model::getNorm(glm::vec3(xIn2, 0, zIn2), glm::vec3(x2, 0, z2), glm::vec3(xIn2, y, zIn2));
			vertices.push_back(VertexFormat(glm::vec3(xIn2, 0, zIn2), blue, glm::vec2(0, 0), verticalWallNormal2));
			vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0), verticalWallNormal2));
			vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1), verticalWallNormal2));

			vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), blue, glm::vec2(0, 1), verticalWallNormal2));
			vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, glm::vec2(1, 1), verticalWallNormal2));
			vertices.push_back(VertexFormat(glm::vec3(x2, 0, z2), blue, glm::vec2(1, 0), verticalWallNormal2));
		}
	}
}

void Bat::Update()
{
	angleOffset = Bats::batAngle;

	rotated = glm::rotate(identityMx, glm::radians(angleOffset), glm::vec3(0.0f, 1.0f, 0.0f));

	cameraMatrixCopy = Camera::cameraMatrix;
}

void Bat::Draw()
{
	glUseProgram(program);

	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrixCopy));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Camera::projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(rotated));

	glm::vec3 lightPos = glm::vec3(Ball::position.x, Ball::position.y + 3, Ball::position.z);
	glUniform3fv(lightPosition, 1, glm::value_ptr(lightPos));
	glUniform3fv(lightColor, 1, glm::value_ptr(Camera::myLightColor));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture->object());
	glUniform1i(texture2d, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, verticesSize);
}
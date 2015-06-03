#include "Brick.h"

using namespace Rendering;
using namespace Models;

Brick::Brick(float pAngle, const glm::vec4 & pColor, float pYpsilon)
{
	Angle = pAngle;
	Color = pColor;
	Ypsilon = pYpsilon;
}

Brick::~Brick()
{}

void Brick::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = Model::brickTexture;
	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec2 zeros = glm::vec2(0, 0);

	float y = Ypsilon + 0.2f;
	
	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 12.0f;
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

		glm::vec3 upNormal = glm::vec3(0, 1, 0);
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), Color, texCoord, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), Color, texCoord2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), Color, texCoordIn, upNormal));

		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), Color, texCoord2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), Color, texCoordIn2, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), Color, texCoordIn, upNormal));

		//outer wall
		glm::vec3 outerWallNormal = Model::getNorm(glm::vec3(x, y, z), glm::vec3(x, Ypsilon, z), glm::vec3(x2, Ypsilon, z2));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), Color, glm::vec2(0, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, Ypsilon, z), Color, glm::vec2(0, 0), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, Ypsilon, z2), Color, glm::vec2(1, 0), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), Color, glm::vec2(0, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), Color, glm::vec2(1, 1), outerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, Ypsilon, z2), Color, glm::vec2(1, 0), outerWallNormal));

		//inner wall
		glm::vec3 innerWallNormal = Model::getNorm(glm::vec3(xIn2, y, zIn2), glm::vec3(xIn2, Ypsilon, zIn2), glm::vec3(xIn, Ypsilon, zIn));
		innerWallNormal *= -1.0f;
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), Color, glm::vec2(0, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, Ypsilon, zIn2), Color, glm::vec2(0, 0), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, Ypsilon, zIn), Color, glm::vec2(1, 0), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), Color, glm::vec2(0, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), Color, glm::vec2(1, 1), innerWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, Ypsilon, zIn), Color, glm::vec2(1, 0), innerWallNormal));
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

		glm::vec3 verticalWallNormal = Model::getNorm(glm::vec3(xIn, Ypsilon, zIn), glm::vec3(x, Ypsilon, z), glm::vec3(xIn, y, zIn));
		verticalWallNormal *= -1.0f;
		vertices.push_back(VertexFormat(glm::vec3(xIn, Ypsilon, zIn), Color, glm::vec2(0, 0), verticalWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, Ypsilon, z), Color, glm::vec2(1, 0), verticalWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), Color, glm::vec2(0, 1), verticalWallNormal));

		vertices.push_back(VertexFormat(glm::vec3(xIn, y, zIn), Color, glm::vec2(0, 1), verticalWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, y, z), Color, glm::vec2(1, 1), verticalWallNormal));
		vertices.push_back(VertexFormat(glm::vec3(x, Ypsilon, z), Color, glm::vec2(1, 0), verticalWallNormal));
	}

	angle += angleDelta;
	angle += angleDelta;
	angle += angleDelta;

	{//second end wall
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		glm::vec3 verticalWallNormal2 = Model::getNorm(glm::vec3(xIn2, Ypsilon, zIn2), glm::vec3(x2, Ypsilon, z2), glm::vec3(xIn2, y, zIn2));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, Ypsilon, zIn2), Color, glm::vec2(0, 0), verticalWallNormal2));
		vertices.push_back(VertexFormat(glm::vec3(x2, Ypsilon, z2), Color, glm::vec2(1, 0), verticalWallNormal2));
		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), Color, glm::vec2(0, 1), verticalWallNormal2));

		vertices.push_back(VertexFormat(glm::vec3(xIn2, y, zIn2), Color, glm::vec2(0, 1), verticalWallNormal2));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), Color, glm::vec2(1, 1), verticalWallNormal2));
		vertices.push_back(VertexFormat(glm::vec3(x2, Ypsilon, z2), Color, glm::vec2(1, 0), verticalWallNormal2));
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

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

	glm::mat4 identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));

	rotated = glm::rotate(identityMx, glm::radians(Angle), glm::vec3(0.0f, 1.0f, 0.0f));

}

void Brick::Update()
{
	cameraMatrixCopy = Camera::cameraMatrix;
}

void Brick::Draw()
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

	//glDrawArrays(GL_LINES, 0, verticesSize);

}
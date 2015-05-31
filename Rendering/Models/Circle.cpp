#include "Circle.h"

using namespace Rendering;
using namespace Models;

float dx = 0.0f;


Circle::Circle()
{}

Circle::~Circle()
{}

void Circle::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = Model::grassTexture;

	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 green = glm::vec4(0, 1, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 nevim = glm::vec4(0.5, 0.5, 0.5, 1);

	glm::vec3 origin = glm::vec3(0, 0, 0);

	float y = 0.0f;

	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 16;

	for (float angle = 0.0f; angle < 2 * pi; angle += angleDelta)
	{
		float x = cos(angle);
		float z = sin(angle);

		float x2 = cos(angle + angleDelta);
		float z2 = sin(angle + angleDelta);

		glm::vec2 zeros = glm::vec2(0, 0);
		glm::vec2 originTex = glm::vec2(0.5, 0.5);

		glm::vec2 texCoord = glm::vec2(x/2 + 0.5, z/2 + 0.5);
		glm::vec2 texCoord2 = glm::vec2(x2 / 2 + 0.5, z2 / 2 + 0.5);

		glm::vec3 upNormal = glm::vec3(0, 1, 0);

		vertices.push_back(VertexFormat(glm::vec3(x, y, z), blue, texCoord, upNormal));
		vertices.push_back(VertexFormat(glm::vec3(x2, y, z2), blue, texCoord2, upNormal));
		vertices.push_back(VertexFormat(origin, blue, originTex, upNormal));
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

	scaledMx = glm::scale(identityMx, glm::vec3(2.0f));

}

void Circle::Update()
{
	dx += 0.02f;
	if (dx > 3.0f)
		dx = 0.0f;

	cameraMatrixCopy = Camera::cameraMatrix;
}

void Circle::Draw()
{
	glUseProgram(program);
	
	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrixCopy));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Camera::projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(scaledMx));

	glm::vec3 lightPos = glm::vec3(Ball::position.x, Ball::position.y + 3, Ball::position.z);
	glUniform3fv(lightPosition, 1, glm::value_ptr(lightPos));
	glUniform3fv(lightColor, 1, glm::value_ptr(Camera::myLightColor));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture->object());
	glUniform1i(texture2d, 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, verticesSize);
}
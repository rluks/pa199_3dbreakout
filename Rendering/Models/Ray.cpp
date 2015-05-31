#include "Ray.h"

using namespace Rendering;
using namespace Models;

Ray::Ray()
{
}


Ray::~Ray()
{
}

void Ray::Create()
{
	GLuint vao;

	tdogl::Bitmap bmp = Model::grassTexture;
	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 blue = glm::vec4(0, 0, 1, 1);

	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec3 somewhere = glm::vec3(1, 0, 1);
	glm::vec3 upNormal = glm::vec3(0, 1, 0);

	vertices.push_back(VertexFormat(origin, red, glm::vec2(0, 0), upNormal));
	vertices.push_back(VertexFormat(somewhere, red, glm::vec2(0, 0), upNormal));

	verticesSize = vertices.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verticesSize, &vertices[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));

	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

	identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));

}

void Ray::Update()
{
	spherePosition = Ball::position;

	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec2 texCoord = glm::vec2(0, 0);
	glm::vec3 upNormal = glm::vec3(0, 1, 0);

	vertices[0] = VertexFormat(spherePosition, red, texCoord, upNormal);
	vertices[1] = VertexFormat(spherePosition + Ball::velocity, red, texCoord, upNormal);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);//update data in buffer!!!
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * verticesSize, &vertices[0], GL_DYNAMIC_DRAW);

	cameraMatrixCopy = Camera::cameraMatrix;
}

void Ray::Draw()
{
	glUseProgram(program);

	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrixCopy));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(Camera::projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(identityMx));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture->object());
	glUniform1i(texture2d, 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, verticesSize);

}

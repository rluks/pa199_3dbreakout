#include "Line.h"


using namespace Rendering;
using namespace Models;

Line::Line(glm::vec3 a, glm::vec3 b, const glm::vec4 &color)
{
	A = a;
	B = b;

	mcolor = color;

	float y = 0.2f;

	A.y = y;
	B.y = y;
}


Line::~Line()
{
}

void Line::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = Model::brickTexture;
	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glm::vec4 nevim = glm::vec4(0.7, 0.7, 0.7, 1);
	glm::vec3 upNormal = glm::vec3(0, 1, 0);

	vertices.push_back(VertexFormat(A, mcolor, glm::vec2(0, 1), upNormal));
	vertices.push_back(VertexFormat(B, nevim, glm::vec2(0, 0), upNormal));

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

	identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));
}

void Line::Update()
{
	cameraMatrixCopy = Camera::cameraMatrix;
}

void Line::Draw()
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

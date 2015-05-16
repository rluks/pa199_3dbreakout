#include "Sphere.h"

using namespace Rendering;
using namespace Models;

float dxR;
Sphere::Sphere()
{
	dxR = 0.0f;
}

Sphere::~Sphere()
{}

void Sphere::Create()
{
	GLuint vao;
	GLuint vbo;

	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile("Textures/ball.png");

	gTexture = new tdogl::Texture(bmp);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	glm::vec4 blue = glm::vec4(0, 0, 1, 1);

	unsigned int rings = 12;
	unsigned int sectors = 24;

	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);

	float pi = 3.14159265358979323846f;

	for (unsigned int r = 0; r < rings; r++) {
		for (unsigned int s = 0; s < sectors; s++) {

			float const y = sin(-pi / 2.0f + pi * r * R);
			float const x = cos(2 * pi * s * S) * sin(pi * r * R);
			float const z = sin(2 * pi * s * S) * sin(pi * r * R);

			//*t++ = s*S;
			//*t++ = r*R;
			glm::vec2 texCoord = glm::vec2(s*S, r*R);

			//*v++ = x * radius;
			//*v++ = y * radius;
			//*v++ = z * radius;
			glm::vec3 vxs = glm::vec3(x, y, z);
			//glm::vec3 vxs = glm::vec3(x, z, y);

			vertices.push_back(VertexFormat(vxs, blue, texCoord));
		}
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

}

void Sphere::Update()
{
	dxR += 1.0f;
	if (dxR > 360.0f)
		dxR = 0.0f;
}

void Sphere::Draw()
{
	glUseProgram(program);
	GLuint camera = glGetUniformLocation(program, "camera");
	GLuint projection = glGetUniformLocation(program, "projection");
	GLuint model = glGetUniformLocation(program, "model");

	GLuint texture2d = glGetUniformLocation(program, "tex");

	glm::vec3 topView = glm::vec3(0, 4, 0.1);
	glm::vec3 perspectiveView = glm::vec3(0, 3, 3);
	glm::vec3 selectedView = perspectiveView;

	//eye - position of the camera's viewpoint, 
	//center - where are you looking, up = up is Y+
	glm::mat4 cameraMatrix = glm::lookAt(selectedView,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	glm::mat4 identityMx = glm::mat4(glm::vec4(-1, 0, 0, 0),
		glm::vec4(0, 1, 0, 0),
		glm::vec4(0, 0, 1, 0),
		glm::vec4(0, 0, 0, 1));

	glm::mat4 rotated = glm::rotate(identityMx, glm::radians(dxR), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(rotated));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture->object());
	glUniform1i(texture2d, 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, verticesSize);
}
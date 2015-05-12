#include "Sphere.h"

using namespace Rendering;
using namespace Models;

std::vector<GLfloat> vertices;
std::vector<GLfloat> normals;
std::vector<GLfloat> texcoords;
std::vector<GLushort> indices;

Sphere::Sphere()
{}

Sphere::~Sphere()
{}

void Sphere::Create()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float radius = 1.0f;
	unsigned int rings = 12;
	unsigned int sectors = 24;

	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);
	unsigned int r, s;

	float pi = 3.14159265358979323846f;

	//std::vector<VertexFormat> vertices;

	vertices.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	texcoords.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();
	for (r = 0; r < rings; r++) {
		for (s = 0; s < sectors; s++) {
			float const y = sin(-pi / 2.0f + pi * r * R);
			float const x = cos(2 * pi * s * S) * sin(pi * r * R);
			float const z = sin(2 * pi * s * S) * sin(pi * r * R);

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = x;
			*n++ = y;
			*n++ = z;
		}
	}

	indices.resize(rings * sectors * 4);
	std::vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}

	/*
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,sizeof(VertexFormat),(void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);*/

}

void Sphere::Update()
{
	//nothing here for the moment
}

void Sphere::Draw()
{
	/*glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 800.0/600.0, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#ifdef DRAW_WIREFRAME
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0, 0, -5);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
	glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
	glPopMatrix();

	
}
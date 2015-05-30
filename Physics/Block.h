#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Block
{
public:
	Block();
	Block(glm::vec3, glm::vec3);
	~Block();

	glm::vec2 normal;
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 middle;

	int number;
	glm::vec4 color;
	int lives;

	static int blockCounter;

	void CalculateMidNorm();
};


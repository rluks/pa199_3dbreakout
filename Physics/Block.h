#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Block
{
public:
	Block();
	Block(glm::vec3, glm::vec3);
	~Block();

	glm::vec2 normal;
	glm::vec3 A;
	glm::vec3 B;
};


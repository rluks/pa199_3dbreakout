#include "Block.h"

Block::Block(){}

Block::Block(glm::vec3 a, glm::vec3 b)
{
	A = a;
	B = b;

	float dx = a.x - b.x;
	float dz = a.z - b.z;

	normal.x = -1.0f * dz;
	normal.y = dx;

	normal = glm::normalize(normal);

	middle = glm::vec3((a.x + b.x) / 2.0f, 0, (a.z + b.z) / 2.0f);
}


Block::~Block()
{

}

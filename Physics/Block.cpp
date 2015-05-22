#include "Block.h"

Block::Block(){}

Block::Block(glm::vec3 a, glm::vec3 b)
{
	A = a;
	B = b;

	float dx = b.x - a.x;
	float dz = b.z - a.z;

	normal.x = -1 * (dz);
	normal.y = dx;
}


Block::~Block()
{

}

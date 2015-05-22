#include "Block.h"

Block::Block(){}

Block::Block(glm::vec3 a, glm::vec3 b)
{
	std::cout << "block a " << a.x << ", " << a.y << ", " << a.z << " b " << b.x << ", " << b.y << ", " << b.z << std::endl;
	A = a;
	B = b;

	float dx = b.x - a.x;
	float dz = b.z - a.z;

	normal.x = -1 * dz;
	normal.y = dx;

	normal = glm::normalize(normal);
}


Block::~Block()
{

}

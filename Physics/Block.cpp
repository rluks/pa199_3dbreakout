#include "Block.h"

int Block::blockCounter = 0;

Block::Block(){}

Block::Block(glm::vec3 a, glm::vec3 b)
{
	A = a;
	B = b;

	CalculateMidNorm();

	/*
	float dx = a.x - b.x;
	float dz = a.z - b.z;

	normal.x = -1.0f * dz;
	normal.y = dx;

	normal = glm::normalize(normal);

	middle = glm::vec3((a.x + b.x) / 2.0f, 0, (a.z + b.z) / 2.0f);*/

	lives = 4;

	blockCounter++;
	number = blockCounter;

	//std::cout << " no." << number << " ax" << A.x << " ay" << A.y << " az"<< A.z << std::endl;
}

void Block::CalculateMidNorm()
{
	float dx = A.x - B.x;
	float dz = A.z - B.z;

	normal.x = -1.0f * dz;
	normal.y = dx;

	normal = glm::normalize(normal);

	middle = glm::vec3((A.x + B.x) / 2.0f, 0, (A.z + B.z) / 2.0f);

}


Block::~Block()
{

}

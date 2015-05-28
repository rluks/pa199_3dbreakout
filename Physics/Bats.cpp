#include "Bats.h"

float Bats::batAngle = 0.0f;

Bats::Bats()
{
	GenerateBats(0.0f);
	GenerateBats(120.0f);
	GenerateBats(240.0f);
}

void Bats::GenerateBats(float startAngle)
{
	float y = 0.2f;

	float pi = 3.14159265358979323846f;
	float angleDelta = pi / 16.0f;
	startAngle = glm::radians(startAngle);
	float endAngle = pi / 6.0f;
	float smallerRadius = 1.7f;
	float radius = 2.0f;
	glm::vec4 color = glm::vec4(0, 0, 0, 0);//pseudocolor

	for (float angle = startAngle; angle < startAngle + endAngle; angle += angleDelta)
	{
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		float x2 = radius * cos(angle + angleDelta);
		float z2 = radius * sin(angle + angleDelta);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		float xIn2 = smallerRadius * cos(angle + angleDelta);
		float zIn2 = smallerRadius * sin(angle + angleDelta);

		glm::vec3 aaa = glm::vec3(xIn, y, zIn);
		glm::vec3 bbb = glm::vec3(xIn2, y, zIn2);
		Block blocktempSide = Block(aaa, bbb);
		blocktempSide.color = color;
		blocktempSide.normal *= -1.0f;
		blocks.push_back(blocktempSide);
	}

}

void Bats::Update()//rotate blocks of bats
{
	//std::cout << "block 0: " << blocks[0].A.x << std::endl;
	for (std::vector<int>::size_type i = 0; i != blocks.size(); i++) {
		Block block = blocks[i];
		block.A = glm::rotate(block.A, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.B = glm::rotate(block.B, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.middle = glm::rotate(block.middle, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.normal = glm::rotate(block.normal, glm::radians(batAngle));
		blocksRotated.push_back(block);
	}
	//std::cout << "block" << blocks[0].A.x << std::endl;

	/*for (std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it)
	{
		Block block = *it;
		block.A = glm::rotate(block.A, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.B = glm::rotate(block.B, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.middle = glm::rotate(block.middle, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.normal = glm::rotate(block.normal, glm::radians(batAngle));
		blocks.
	}*/


}


Bats::~Bats()
{
}

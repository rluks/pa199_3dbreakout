#include "Bats.h"

float Bats::batAngle = 0.0f;
float Bats::batAngleIncrement = 0.0f;

Bats::Bats(){}
Bats::~Bats(){}

Bats::Bats(int useless)
{
	GenerateBats(0.0f);
	GenerateBats(120.0f);
	GenerateBats(240.0f);
}

void Bats::GenerateBats(float startAngle)
{
	//std::cout << "GenerateBats" << std::endl;

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

	

	{//one side of bat
		float angle = startAngle;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		float xIn = smallerRadius * cos(angle);
		float zIn = smallerRadius * sin(angle);

		glm::vec3 aaa = glm::vec3(x, y, z);
		glm::vec3 bbb = glm::vec3(xIn, y, zIn);
		Block blocktempSide = Block(aaa, bbb);
		blocktempSide.color = color;
		blocktempSide.normal *= -1.0f;
		blocks.push_back(blocktempSide);
	}

		{//other side of bat
			float angle = startAngle + endAngle;
			float x = radius * cos(angle);
			float z = radius * sin(angle);

			float xIn = smallerRadius * cos(angle);
			float zIn = smallerRadius * sin(angle);

			glm::vec3 aaa = glm::vec3(x, y, z);
			glm::vec3 bbb = glm::vec3(xIn, y, zIn);
			Block blocktempSide = Block(aaa, bbb);
			blocktempSide.color = color;
			blocks.push_back(blocktempSide);
		}


}

void Bats::Update()
{
	batAngle += batAngleIncrement;

	blocksRotated.clear();
	for (std::vector<int>::size_type i = 0; i != blocks.size(); i++) {
		Block block = blocks[i];
		block.A = glm::rotate(block.A, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		block.B = glm::rotate(block.B, glm::radians(batAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		block.CalculateMidNorm();
		blocksRotated.push_back(block);
	}
}

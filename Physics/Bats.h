#pragma once

#include "Block.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Bats
{
	public:
		Bats();
		Bats(int);
		~Bats();

		std::vector<Block> blocks;
		std::vector<Block> blocksRotated;
		void GenerateBats(float);
		void Update();

		static float batAngle;
		static float batAngleIncrement;
};


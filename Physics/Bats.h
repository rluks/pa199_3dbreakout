#pragma once

#include "Block.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Bats
{
	public:
		Bats();
		~Bats();

		std::vector<Block> blocks;
		void GenerateBats(float);

		static float batAngle;
};


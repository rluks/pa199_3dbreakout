#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\Managers\TimeManager.h"

class Ball
{
public:
	Ball();
	~Ball();
	static glm::vec3 position;
	static glm::vec3 velocity;
	static void Update();

	static double startTime;
	static double endTime;
	static float radius;
};


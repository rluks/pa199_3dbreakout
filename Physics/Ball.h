#pragma once

#include <iostream>


#include <string>
#include <iomanip>

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
	static void CorrectionUpdate(double);

	static double startTime;
	static double endTime;
	static float radius;

	static bool enableMovement;
	static bool selectVelocity;
	static float velocityAngle;
};


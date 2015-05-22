#include "Ball.h"

float Ball::radius = 0.125;
glm::vec3 Ball::position = glm::vec3(0, radius, 0);
glm::vec3 Ball::velocity = glm::vec3(0.2, 0, 0.3);
double Ball::startTime = 0.0;
double Ball::endTime = 0.0;


Ball::Ball()
{
	
}


Ball::~Ball()
{
}



void Ball::Update()
{
	endTime = TimeManager::GetTime();

	double elapsedTime;
	if (startTime == 0.0)//start
		elapsedTime = 0.1;
	else
		elapsedTime = endTime - startTime;

	//std::cout << "elapsed:" << elapsedTime << std::endl;

	position.x += elapsedTime * velocity.x;
	position.z += elapsedTime * velocity.z;

	startTime = endTime;

	//std::cout << "pos.x" << position.x << std::endl;

	float distanceFromCenter = sqrt(position.x * position.x + position.z * position.z);

	
	
	/*if (distanceFromCenter > 0.0f && distanceFromCenter < 0.5f){
		float vx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//float vx = 0.8f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.9f - 0.8f)));
		float vz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//float vz = 0.4f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.6f - 0.4f)));

		if (velocity.x < 0.0f)
			vx *= -1.0f;
		velocity.x = vx;

		if (velocity.z < 0.0f)
			vz *= -1.0f;
		velocity.z = vz;
	}*/

	if (distanceFromCenter+radius > 2.0f)
	{
		velocity.x *= -1.0f;
		velocity.z *= -1.0f;
	}
}

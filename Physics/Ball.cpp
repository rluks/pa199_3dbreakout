#include "Ball.h"

float Ball::radius = 0.125;
glm::vec3 Ball::position = glm::vec3(0.8, radius, 1.3);
glm::vec3 Ball::velocity = glm::vec3(0.23, 0, 0.3);
double Ball::startTime = 0.0;
double Ball::endTime = 0.0;
bool Ball::enableMovement = true;


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

	startTime = endTime;
	
	if (enableMovement){
		position.x += elapsedTime * velocity.x;
		position.z += elapsedTime * velocity.z;

		float distanceFromCenter = sqrt(position.x * position.x + position.z * position.z);

		if (distanceFromCenter + radius > 2.0f)
		{
			velocity.x *= -1.0f;
			velocity.z *= -1.0f;
		}
	}


}

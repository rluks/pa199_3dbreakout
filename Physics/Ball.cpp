#include "Ball.h"

glm::vec3 Ball::position = glm::vec3(0, 0, 0);
glm::vec3 Ball::velocity = glm::vec3(0.5, 0, 0);
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
}

#include "Ball.h"

float Ball::radius = 0.125;
glm::vec3 Ball::position = glm::vec3(1.0, radius, 1.3);
glm::vec3 Ball::velocity = glm::vec3(-0.23, 0, -0.4);
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
			//velocity.x *= -1.0f;
			//velocity.z *= -1.0f;

			//float dx = a.x - b.x;
			//float dz = a.z - b.z;

			float dx = -0.1f;
			float dz = -0.1f;

			//float dx = b.x - a.x;
			//float dz = b.z - a.z;

			float normalx = -1 * dz;
			float normaly = dx;

			glm::vec3 vel = Ball::velocity;
			glm::vec3 normal = glm::vec3(normalx, 0, normaly);
			normal = glm::normalize(normal);
			Ball::velocity = vel - 2 * glm::dot(vel, normal) * normal;

			velocity.x *= -1.0f;
			velocity.z *= -1.0f;
		}
	}


}

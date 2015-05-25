#include "Ball.h"

float Ball::radius = 0.125f;
glm::vec3 Ball::position = glm::vec3(-1.6, radius, -0.3);
glm::vec3 Ball::velocity = 1.25f*glm::vec3(0.99, 0, -0.1);
double Ball::startTime = 0.0;
double Ball::endTime = 0.0;
bool Ball::enableMovement = true;
bool Ball::selectVelocity = false;
float Ball::velocityAngle = 0.0f;


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

	if (selectVelocity){
		float pi = 3.14159265358979323846f;
		float angleDelta = pi / 128.0f;

		float x = cos(velocityAngle);
		float z = sin(velocityAngle);

		velocity.x = x;
		velocity.z = z;

		velocityAngle += angleDelta;
	}
	
	if (enableMovement){

		position.x += elapsedTime * velocity.x;
		position.z += elapsedTime * velocity.z;

		glm::vec2 fakenormal = glm::vec2(0.0f - position.x, 0.0f - position.z);
		float distanceFromCenter = glm::length(fakenormal);

		if (distanceFromCenter + radius > 2.0f)
		{
			fakenormal = glm::normalize(fakenormal);
			fakenormal = -1.0f * fakenormal;

			//std::cout << "ball has reached outer wall" << std::endl;
			//std::cout << "x: " << position.x << " y: " << position.z << std::endl;

			glm::vec3 vel = velocity;
			glm::vec3 normal = glm::vec3(fakenormal.x, 0, fakenormal.y);
			normal = glm::normalize(normal);
			velocity = vel - 2 * glm::dot(vel, normal) * normal;
		}
	}


}

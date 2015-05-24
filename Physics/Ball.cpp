#include "Ball.h"

float Ball::radius = 0.125f;
glm::vec3 Ball::position = glm::vec3(1.0, radius, 1.3);
glm::vec3 Ball::velocity = 8.0f*glm::vec3(-0.23, 0, -0.4);
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
		float angleDelta = pi / 64.0f;

		float x = cos(velocityAngle);
		float z = sin(velocityAngle);

		velocity.x = x;
		velocity.z = z;

		velocityAngle += angleDelta;
	}
	
	if (enableMovement){

		/*if (velocity.x < 0)
			velocity.x = velocity.x - 0.01f;
		else
			velocity.x = velocity.x + 0.01f;

		if (velocity.z < 0)
			velocity.z = velocity.z - 0.01f;
		else
			velocity.z = velocity.z + 0.01f;*/

		position.x += elapsedTime * velocity.x;
		position.z += elapsedTime * velocity.z;

		glm::vec2 fakenormal = glm::vec2(0.0f - position.x, 0.0f - position.z);
		float distanceFromCenter = glm::length(fakenormal);//sqrt(position.x * position.x + position.z * position.z);

		if (distanceFromCenter + radius > 2.0f)
		{
			fakenormal = glm::normalize(fakenormal);
			fakenormal = -1.0f * fakenormal;

			std::cout << "ball has reached outer wall" << std::endl;
			std::cout << "x: " << position.x << " y: " << position.z << std::endl;

			float dx = fakenormal.x;
			float dz = fakenormal.y;

			std::cout << "dx:" << dx << " dz: " << dz << std::endl;

			/*float normalx = -1.0f * dz;//actual dx
			float normaly = dx;

			std::cout << "circle nx:" << normalx << " ny: " << normaly << std::endl;*/

			glm::vec3 vel = velocity;
			glm::vec3 normal = glm::vec3(dx, 0, dz);
			normal = glm::normalize(normal);
			velocity = vel - 2 * glm::dot(vel, normal) * normal;

			//velocity.x *= -1.0f;
			//velocity.z *= -1.0f;
		}
	}


}

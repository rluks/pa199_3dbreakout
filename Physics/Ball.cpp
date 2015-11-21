#include "Ball.h"

float Ball::radius = 0.125f;
glm::vec3 Ball::position = glm::vec3(1.0, radius, 1.0);
glm::vec3 Ball::velocity = 1.0f*glm::vec3(-1.0, 0, -1.0);
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

void Ball::CorrectionUpdate(double elapsedTime)
{
	position.x += elapsedTime * velocity.x;
	position.z += elapsedTime * velocity.z;
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
		float angleDelta = pi / 100.0f;

		float x = cos(velocityAngle);
		float z = sin(velocityAngle);

		velocity.x = x;
		velocity.z = z;

		velocityAngle += angleDelta;
	}
	
	if (enableMovement){
		std::setw(2);
		std::setprecision(5);
		//std::cout.precision(5);
		//std::cout << "el" << std::to_string(elapsedTime) << std::endl;
		std::cout << std::fixed << std::setw(11) << std::setprecision(6)
			<< std::setfill('0') << elapsedTime << std::endl;
		position.x += elapsedTime * velocity.x;
		position.z += elapsedTime * velocity.z;
	}


}

#include "InputManager.h"


bool InputManager::switchShaders = false;
bool InputManager::rotate = false;

InputManager::InputManager()
{
	bool Continue = TRUE;
	int KeyEvents = 0;
	int MouseEvents = 0;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//cout << "Key Events   : " << endl;
	//cout << "Mouse Events : " << flush;

	KeyWhere.X = 15;
	KeyWhere.Y = 0;
	MouseWhere.X = 15;
	MouseWhere.Y = 1;
	EndWhere.X = 0;
	EndWhere.Y = 3;


}

void InputManager::stopBall()
{
	Ball::enableMovement = false;
}

void InputManager::playBall()
{
	Ball::enableMovement = true;
}

void InputManager::switchCamera()
{
	Camera::SwitchViews();
	//switchShaders = !switchShaders;
}

void InputManager::left()
{
	Bats::batAngleIncrement = 1.0f;
}

void InputManager::right()
{
	Bats::batAngleIncrement = -1.0f;
}

void InputManager::stopTurning()
{
	Bats::batAngleIncrement = 0.0f;
}

void InputManager::zoomIn()
{
	Camera::UpdateProjectionMatrix(-5.0f);
}

void InputManager::zoomOut()
{
	Camera::UpdateProjectionMatrix(5.0f);
}

void InputManager::Rotate()
{
	rotate = !rotate;

	if (rotate){
		Camera::Rotate();
	}
	else{
		Camera::DisableRotate();
	}
}

void InputManager::UpCamera()
{
	Camera::Translate(0.5f, 0.0f, 0.0f);
}

void InputManager::DownCamera()
{
	Camera::Translate(-0.5f, 0.0f, 0.0f);
}

void InputManager::LeftCamera()
{
	Camera::Translate(0.0f, -0.5f, 0.0f);
}

void InputManager::RightCamera()
{
	Camera::Translate(0.0f, 0.5f, 0.0f);
}

void InputManager::ForwardCamera()
{
	Camera::Translate(0.0f, 0.0f, -0.5f);
}

void InputManager::BackwardCamera()
{
	Camera::Translate(0.0f, 0.0f, 0.5f);
}

void InputManager::ConfirmVelocity()
{
	//std::cout << "Position: " << Ball::position.x << ", " << Ball::position.z << " Velocity: " << Ball::velocity.x << ", " << Ball::velocity.z << std::endl;
	Ball::enableMovement = true;
	Ball::selectVelocity = false;
}

void InputManager::SelectVelocity()
{
	Ball::enableMovement = false;
	Ball::selectVelocity = true;
}
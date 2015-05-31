#include "Camera.h"

float Camera::FoV = 35.0f;
float Camera::RotateDelta = 0.0f;
float Camera::RotateAngle = 0.0f;
glm::mat4 Camera::projectionMatrix = glm::perspective(glm::radians(FoV), 800.0f / 600.0f, 0.1f, 10.0f);

glm::vec3 Camera::topView = glm::vec3(0, 6, 0.1);
glm::vec3 Camera::perspectiveView = glm::vec3(0, 4, 4);
glm::vec3 Camera::ballView = Ball::position;
glm::vec3 Camera::selectedView = perspectiveView;

glm::vec3 Camera::center = glm::vec3(0, 0, 0);

glm::vec3 Camera::myLightColor = glm::vec3(1, 1, 1);

//eye - position of the camera's viewpoint, 
//center - where are you looking, up = up is Y+
glm::mat4 Camera::cameraMatrix = glm::lookAt(Camera::selectedView, 
												center, 
												glm::vec3(0, 1, 0));

Camera::Camera(){}
Camera::~Camera(){}

void Camera::SwitchViews()
{
	if (selectedView == perspectiveView)
		selectedView = topView;
	else if (selectedView == topView)
		selectedView = ballView;
	else
		selectedView = perspectiveView;
}

void Camera::UpdateProjectionMatrix(float pFoV)
{
	FoV += pFoV;
}

void Camera::Update()
{
	RotateAngle += RotateDelta;

	glm::vec3 selectedViewTemp = Camera::selectedView;
	glm::vec3 centerTemp = center;

	if (selectedView == ballView){
		centerTemp = Ball::position;
		centerTemp.x *= -1.0f;
		selectedViewTemp = Ball::position + glm::vec3(0, 2, 2);
	}

	cameraMatrix = glm::lookAt(selectedViewTemp,
		centerTemp,
		glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(glm::radians(FoV), 
										800.0f / 600.0f, 
										0.1f, 10.0f);

	cameraMatrix = glm::rotate(cameraMatrix, glm::radians(RotateAngle), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Rotate()
{
	RotateDelta = 1.0f;
}

void Camera::DisableRotate()
{
	RotateDelta = 0.0f;
}

void Camera::Translate(float height, float width, float depth)
{
	selectedView.y += height;
	selectedView.x += width;
	selectedView.z += depth;

	center.y += height;
	center.x += width;
	center.z += depth;
}

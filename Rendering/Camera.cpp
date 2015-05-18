#include "Camera.h"

float Camera::FoV = 35.0f;
glm::mat4 Camera::projectionMatrix = glm::perspective(glm::radians(FoV), 800.0f / 600.0f, 0.1f, 10.0f);
glm::vec3 Camera::topView = glm::vec3(0, 6, 0.1);
glm::vec3 Camera::perspectiveView = glm::vec3(0, 4, 4);
glm::vec3 Camera::selectedView = perspectiveView;

Camera::Camera(){}
Camera::~Camera(){}

void Camera::SwitchViews()
{
	if (selectedView == perspectiveView)
		selectedView = topView;
	else
		selectedView = perspectiveView;
}

void Camera::UpdateProjectionMatrix(float pFoV)
{
	FoV += pFoV;
	projectionMatrix = glm::perspective(glm::radians(FoV), 800.0f / 600.0f, 0.1f, 10.0f);
}

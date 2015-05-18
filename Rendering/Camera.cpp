#include "Camera.h"

glm::mat4 Camera::projectionMatrix = glm::perspective(glm::radians(35.0f), 800.0f / 600.0f, 0.1f, 10.0f);
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

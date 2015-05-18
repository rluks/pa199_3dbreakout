#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	static void SwitchViews();
	static glm::mat4 projectionMatrix;
	static glm::vec3 topView;
	static glm::vec3 perspectiveView;
	static glm::vec3 selectedView;

};


#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Physics/Ball.h"

class Camera
{
public:
	Camera();
	~Camera();
	static void SwitchViews();
	static void UpdateProjectionMatrix(float);
	static void Rotate();
	static void DisableRotate();

	static void Translate(float height, float width, float depth);

	static void Update();

	static glm::mat4 projectionMatrix;
	static glm::mat4 cameraMatrix;

	static glm::vec3 topView;
	static glm::vec3 perspectiveView;
	static glm::vec3 selectedView;
	static glm::vec3 ballView;

	static glm::vec3 myLightColor;


	static float FoV;
	static float RotateDelta;
	static float RotateAngle;

private:
	static glm::vec3 center;
};


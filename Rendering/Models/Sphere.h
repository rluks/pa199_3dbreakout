#pragma once

#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

#include "..\..\Physics\Ball.h"

namespace Rendering
{
	namespace Models
	{
		class Sphere : public Models::Model
		{
		public:
			Sphere();
			~Sphere();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;
			glm::vec3 spherePosition;
			glm::mat4 identityMx;
			glm::mat4 modelmx;
			glm::mat4 rotated;
			glm::mat4 scaledMx;
		};
	}
}
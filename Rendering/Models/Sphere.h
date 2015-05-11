#pragma once

#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

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
		};
	}
}
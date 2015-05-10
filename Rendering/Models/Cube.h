#pragma once

#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Rendering
{
	namespace Models
	{
		class Cube : public Models::Model
		{
		public:
			Cube();
			~Cube();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;
		};
	}
}
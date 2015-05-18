#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"

namespace Rendering
{
	namespace Models
	{
		class Brick : public Models::Model
		{
		public:
			Brick(float);
			~Brick();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			float Angle;
		private:
			glm::mat4 rotated;
		};
	}
}
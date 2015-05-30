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
			Brick(float, const glm::vec4 &, float);
			~Brick();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			float Angle;
			glm::vec4 Color;
			float Ypsilon;

			std::vector<VertexFormat> vertices;
		private:
			glm::mat4 rotated;
		};
	}
}
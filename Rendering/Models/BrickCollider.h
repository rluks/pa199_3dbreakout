#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"

namespace Rendering
{
	namespace Models
	{
		class BrickCollider : public Models::Model
		{
		public:
			BrickCollider(float);
			~BrickCollider();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			float Angle;
			std::vector<VertexFormat> vertices;
		private:
			glm::mat4 rotated;
		};
	}
}
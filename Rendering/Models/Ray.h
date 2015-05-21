#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"

#include "..\..\Physics\Ball.h"

namespace Rendering
{
	namespace Models
	{
		class Ray : public Models::Model
		{
		public:
			Ray();
			~Ray();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			glm::vec3 spherePosition;
			glm::mat4 identityMx;
			glm::mat4 modelmx;

			std::vector<VertexFormat> vertices;
			GLuint vbo;
		};
	}
}


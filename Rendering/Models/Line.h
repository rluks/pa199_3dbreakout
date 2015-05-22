#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"

namespace Rendering
{
	namespace Models
	{
		class Line : public Models::Model
		{
		public:
			Line(glm::vec3, glm::vec3, const glm::vec4 &);
			~Line();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			glm::mat4 identityMx;
			std::vector<VertexFormat> vertices;

			glm::vec3 A;
			glm::vec3 B;

			glm::vec4 mcolor;
			
		};
	}
}

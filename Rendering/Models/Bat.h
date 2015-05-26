#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"
#include "..\..\Managers\InputManager.h"
#include "..\..\Physics\Bats.h"

namespace Rendering
{
	namespace Models
	{
		class Bat : public Models::Model
		{
		public:
			Bat(float);
			~Bat();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			float dxB;//for testing
			float angle;//for vertex generations
			float angleOffset;//for controls
		private:
			void generateBatVertices(float, std::vector<VertexFormat>&);
			glm::mat4 identityMx;
			glm::mat4 rotated;
		};
	}
}
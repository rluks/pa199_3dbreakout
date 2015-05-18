#pragma once

#include "Model.h"
#include "../tdogl/Texture.h"

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

			float angle;//for vertex generations
			static float angleOffset;//for controls
		private:
			void generateBatVertices(float, std::vector<VertexFormat>&);
		};
	}
}
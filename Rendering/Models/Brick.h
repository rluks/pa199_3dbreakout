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
			Brick();
			~Brick();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;
		};
	}
}
#pragma once

#include "Model.h"

namespace Rendering
{
	namespace Models
	{
		class Circle : public Models::Model
		{
		public:
			Circle();
			~Circle();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			glm::mat4 scaledMx;
		};
	}
}
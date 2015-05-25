#pragma once

#include <map>

#include "Shader_Manager.h"

#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Sphere.h"
#include "../Rendering/Models/Circle.h"
#include "../Rendering/Models/Brick.h"
#include "../Rendering/Models/Bat.h"
#include "../Rendering/Models/Ray.h"
#include "../Rendering/Models/BrickCollider.h"
#include "../Rendering/Models/Line.h"

#include "InputManager.h"

using namespace Rendering;

namespace Managers
{
	class Models_Manager
	{
		public:
			Models_Manager();
			~Models_Manager();

			void Draw();
			void Update();

			void DeleteModel(const std::string& gameModelName);
			const IGameObject& GetModel(const std::string& gameModelName) const;
			void AddLine(glm::vec3, glm::vec3, const glm::vec4 &);

			static std::string GetColorName(const glm::vec4 &);

		private:
			std::map<std::string, IGameObject*> gameModelList;
		};
}
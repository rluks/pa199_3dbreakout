#pragma once
#include "glm\glm.hpp" //installed with NuGet

namespace Rendering
{
	struct VertexFormat
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture;
		glm::vec3 normal;

		VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor, const glm::vec2 &iTex, const glm::vec3 &iNormal)
		{
			position = iPos;
			color = iColor;
			texture = iTex;
			normal = iNormal;
		}
	};
}
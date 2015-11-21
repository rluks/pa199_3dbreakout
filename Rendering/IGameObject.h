#pragma once

#include <vector>
#include <iostream>

#include "..\OpenGLIncludes.h"

//#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 
//#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

#include "VertexFormat.h"

namespace Rendering
{
	class IGameObject
	{
		public:
			virtual ~IGameObject() = 0;

			virtual void Draw() = 0;
			virtual void Update() = 0;
			virtual void SetProgram(GLuint shaderName) = 0;
			virtual void Destroy() = 0;

			virtual GLuint GetVao() const = 0;
			virtual const std::vector<GLuint>& GetVbos() const = 0;
	};

	inline IGameObject::~IGameObject()
	{//blank
	}
}
#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "..\OpenGLIncludes.h"

//..\ subfolder!
//#include "..\..\packages\nupengl.core.0.1.0.1\build\native\include\GL\glew.h" 
//#include "..\..\packages\nupengl.core.0.1.0.1\build\native\include\GL\freeglut.h" 

namespace Managers
{
	class Shader_Manager
	{
		public:
			Shader_Manager(void);
			~Shader_Manager(void);

			//modify char* to std::string
			void CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
			static const GLuint GetShader(const std::string&);

		private:

			std::string ReadShader(const std::string& filename);
			GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);

			static std::map<std::string, GLuint> programs;
	};
}
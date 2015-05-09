#pragma once

//..\ subfolder!
#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 
#include "..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

#include <iostream>

namespace Core
{
	class Shader_Loader
	{
		private:
			std::string ReadShader(char *filename); //reads and returns the contents of a file
			GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName); //creates and compiles a shader

		public:
			Shader_Loader(void);//constructor
			~Shader_Loader(void);

			GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);
	};
}
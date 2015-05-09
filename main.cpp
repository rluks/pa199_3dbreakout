
//(GL Extension Wrangler), which adds support for the newest OpenGL versions eg. OpenGL  version 4.5. 
//This means that we can access and play with OpenGL’s newest functions
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 

//setting up a window, initializing OpenGL contexts and getting input from mouse/keyboard. 
//Beside FreeGLUT there are other libraries that can be used with OpenGL. eg: SDL, GLFW, GLUT, GLOW, native code, etc.
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

//includes
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

//other includes
#include "Core\Shader_Loader.h"
#include "Core\GameModels.h"

GLuint program;
Models::GameModels* gameModels;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//rgba

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();//swaps between back buffer and front buffer. Remember that we are using double buffering.
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void printGLInfo(bool verbose = false)
{
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	if (verbose)
	{
		int n_extension_num;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n_extension_num);
		for (int i = 0; i < n_extension_num; ++i) {
			const char *p_s_ext_name = (const char*)glGetStringi(GL_EXTENSIONS, i);
			std::cout << p_s_ext_name << std::endl;
		}
	}
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");

	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//GL_POINT, GL_FILL
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);// initialize the GLUT library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//Z buffer, Double Buffering, 32-bit Framebuffer for the four 8-bit color channels: Red, Green, Blue, and Alpha
	//glutInitWindowPosition(100, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("PA199 3D Breakout");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();

	printGLInfo();
	if (!glewIsSupported("GL_VERSION_3_0"))
	{
		std::cerr << "error: OpenGL 3.0 not supported!" << std::endl;
		return 1;
	}

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();//GLUT processing loop, interupted only by callbacks

	//cleanup
	delete gameModels;
	glDeleteProgram(program);

	return 0;
}

//(GL Extension Wrangler), which adds support for the newest OpenGL versions eg. OpenGL  version 4.5. 
//This means that we can access and play with OpenGL’s newest functions
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 

//setting up a window, initializing OpenGL contexts and getting input from mouse/keyboard. 
//Beside FreeGLUT there are other libraries that can be used with OpenGL. eg: SDL, GLFW, GLUT, GLOW, native code, etc.
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

//other includes
#include <iostream>

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//rgba

	glutSwapBuffers();//swaps between back buffer and front buffer. Remember that we are using double buffering.
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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("PA199 3D Breakout");

	glewInit();

	printGLInfo(true);
	if (!glewIsSupported("GL_VERSION_3_0"))
	{
		std::cerr << "error: OpenGL 3.0 not supported!" << std::endl;
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h"
#include "..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h"
#include <iostream>

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//rgba

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("PA199 3D Breakout");

	glEnable(GL_DEPTH_TEST);

	// register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
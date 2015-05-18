#pragma once

#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"
#include "Managers\InputManager.h"

using namespace Core;
using namespace Init;

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		InputManager::left();
		break;
	case GLUT_KEY_RIGHT:
		InputManager::right();
		break;
	}
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		InputManager::zoomIn();
	}
	else
	{
		InputManager::zoomOut();
	}

	return;
}

void keyboardInput(unsigned char key, int x, int y)
{
	if (key == 'r')
		InputManager::Rotate();

	if (key == 'c')
		InputManager::switchCamera();

	if (key == 'w')
		InputManager::Up();
	if (key == 's')
		InputManager::Down();

	return;
}

int main(int argc, char **argv)
{
	WindowInfo window(std::string("PA199 3D Breakout"),
		400, 200,//position
		800, 600, //size
		true);//reshape

	ContextInfo context(3, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init_GLUT::init(window, context, frameBufferInfo);

	IListener* scene = new Managers::Scene_Manager();
	Init::Init_GLUT::setListener(scene);

	InputManager* input = new InputManager();
	glutSpecialFunc(SpecialInput);
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboardInput);

	Init_GLUT::run();

	delete scene;
	return 0;
}


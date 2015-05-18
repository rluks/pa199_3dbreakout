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
		//do something here
		std::cout << "w" << std::endl;
		break;
	case GLUT_KEY_DOWN:
		std::cout << "Switching camera..." << std::endl;
		InputManager::switchCamera();
		break;
	case GLUT_KEY_LEFT:
		std::cout << "a" << std::endl;
		InputManager::left();
		break;
	case GLUT_KEY_RIGHT:
		std::cout << "d" << std::endl;
		InputManager::right();
		break;
	}
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

	Init_GLUT::run();

	delete scene;
	return 0;
}


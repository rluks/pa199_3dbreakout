#pragma once

#include "Core\Init\Init_GLUT.h"

using namespace Core;
using namespace Init;

int main(int argc, char **argv)
{
	WindowInfo window(std::string("PA199 3D Breakout"),
		400, 200,//position
		800, 600, //size
		true);//reshape

	ContextInfo context(3, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init_GLUT::init(window, context, frameBufferInfo);

	Init_GLUT::run();

	return 0;
}
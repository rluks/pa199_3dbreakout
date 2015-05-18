#include "Init_GLUT.h"

using namespace Core::Init;

Core::IListener* Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::init(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo,
	const Core::FramebufferInfo& framebufferInfo)
{
	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = {"fake", NULL};
	glutInit(&fakeargc, fakeargv);

	//if we set the GL context to Compatibility mode we can’t use a lower version. 
	//This works only if you are in a Core context mode
	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version, contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		//As I said in part II, version doesn't matter
		// in Compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebufferInfo.flags);

	windowInformation = windowInfo;
	glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;

	//callbacks
	glutIdleFunc(idleCallback);//called when events are not being received
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);//triggered when the window is reshaped
	//glutKeyboardFunc(keyboardCallback);

	//init GLEW, this can be called in main.cpp
	Init::Init_GLEW::Init();

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);
}

//starts the rendering Loop
void Init_GLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0, 0.0, 0.0, 1);
		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(width, height,
				windowInformation.width,
				windowInformation.height);
		}
		windowInformation.width = width;
		windowInformation.height = height;
	}
}

void Init_GLUT::closeCallback()
{
	close();
}



void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::setListener(Core::IListener*& iListener)
{
	listener = iListener;
}

void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo){

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	if (false)
	{
		int n_extension_num;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n_extension_num);
		for (int i = 0; i < n_extension_num; ++i) {
			const char *p_s_ext_name = (const char*)glGetStringi(GL_EXTENSIONS, i);
			std::cout << p_s_ext_name << std::endl;
		}
	}
}
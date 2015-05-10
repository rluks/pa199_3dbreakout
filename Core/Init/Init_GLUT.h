#pragma once

#include <iostream>

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "Init_GLEW.h"
#include "IListener.h"

namespace Core 
{
	namespace Init
	{
		class Init_GLUT
		{

			public:  
				static void init(const Core::WindowInfo& window,
					const Core::ContextInfo& context,
					const Core::FramebufferInfo& framebufferInfo);

			public:
				static void setListener(Core::IListener*& iListener);

				static void run();//called from outside
				static void close();

				void enterFullscreen();
				void exitFullscreen();

				static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
					const Core::ContextInfo& context);
			private:
				static Core::IListener* listener;
				static Core::WindowInfo windowInformation;

				static void idleCallback(void);
				static void displayCallback(void);
				static void reshapeCallback(int width, int height);
				static void closeCallback();
		};
	}
}
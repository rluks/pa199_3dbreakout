#pragma once

#include <iostream>

#include "..\..\OpenGLIncludes.h"

//#include "..\..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\glew.h" 
//#include "..\..\..\packages\nupengl.core.0.0.0.1\build\native\include\GL\freeglut.h" 

namespace Core{

	namespace Init{

		class Init_GLEW
		{
			public:
				static void Init();
		};
	}
}
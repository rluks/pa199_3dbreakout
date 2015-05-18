#pragma once

#include <windows.h>
#include <iostream>

#include "..\OpenGLIncludes.h"
#include "..\Rendering\Models\Model.h"

using namespace std;

class InputManager
{
	public:
		InputManager();
		void Watch();
		void SpecialInput(int key, int x, int y);

		static void left();
		static void right();
		static void switchCamera();

		static float batAngle;

	private:
		HANDLE hIn;
		HANDLE hOut;
		COORD KeyWhere;
		COORD MouseWhere;
		COORD EndWhere;
		INPUT_RECORD InRec;
		DWORD NumRead;

		bool Continue;
		int KeyEvents;
		int MouseEvents;
};

#pragma once

#include <windows.h>
#include <iostream>

#include "..\OpenGLIncludes.h"
#include "..\Rendering\Models\Model.h"
#include "..\Rendering\Camera.h"

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
		static void zoomIn();
		static void zoomOut();
		static void Rotate();

		static void Up();
		static void Down();

		static float batAngle;
		static bool switchShaders;

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

		static bool rotate;
};

#pragma once

#include <windows.h>
#include <iostream>

#include "..\OpenGLIncludes.h"
#include "..\Rendering\Models\Model.h"
#include "..\Rendering\Camera.h"
#include "..\Physics\Ball.h"
#include "..\Physics\Bats.h"

using namespace std;

class InputManager
{
	public:
		InputManager();

		void SpecialInput(int key, int x, int y);

		static void left();
		static void right();
		static void stopTurning();

		static void switchCamera();
		static void zoomIn();
		static void zoomOut();
		static void Rotate();

		static void UpCamera();
		static void DownCamera();
		static void LeftCamera();
		static void RightCamera();
		static void ForwardCamera();
		static void BackwardCamera();

		static void stopBall();
		static void playBall();

		static bool switchShaders;

		static void SelectVelocity();
		static void ConfirmVelocity();

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

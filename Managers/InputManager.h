#pragma once

#include <windows.h>
#include <iostream>

using namespace std;

class InputManager
{
	public:
		InputManager();
		void Watch();

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

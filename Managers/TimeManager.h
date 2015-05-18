#pragma once

#include <chrono>	
#include <thread>	

class TimeManager
{
public:
	// This returns the current time in seconds (since 1/1/1970, call "epoch")
	static double TimeManager::GetTime();

	// This calculates our current scene's frames per second and displays it in the console
	static double CalculateFrameRate();

	// This is the time slice that stores the total time in seconds that has elapsed since the last frame
	static double DeltaTime;

	// This is the current time in seconds
	static double CurrentTime;
};
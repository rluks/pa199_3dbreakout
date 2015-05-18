#pragma once

#include <chrono>	
#include <thread>	

class TimeManager
{
public:
	// This returns the current time in seconds (since 1/1/1970, call "epoch")
	static double TimeManager::GetTime();
};
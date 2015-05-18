#include "TimeManager.h"

// This returns the current time in seconds (uses C++ 11 system_clock)
double TimeManager::GetTime()
{
	// Grab the current system time since 1/1/1970, otherwise know as the Unix Timestamp or Epoch
	auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();

	// Convert the system time to milliseconds
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();

	// Return the time in seconds and give us a fractional value (important!)
	return ms * 0.001;
}
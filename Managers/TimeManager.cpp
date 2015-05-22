#include "TimeManager.h"


double TimeManager::DeltaTime;
double TimeManager::CurrentTime;

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

double TimeManager::CalculateFrameRate()
{
	bool writeToConsole = false;

	// Below we create a bunch of static variables to track the deltas of the time.

	static double framesPerSecond = 0.0f;								// This will store our fps
	static double startTime = GetTime();								// This will hold the time per second to test against
	static double lastTime = GetTime();									// This will hold the time from the last frame
	static char strFrameRate[50] = { 0 };								// We will store the string here for the window title
	static double currentFPS = 0.0f;									// This stores the current frames per second

	// Grab the current time in seconds from our environment's time function wrapped in our WindowManager	
	CurrentTime = GetTime();

	// Calculate our delta time, which is the time that has elapsed since the last time we checked the time
	DeltaTime = CurrentTime - lastTime;

	// Now store the lastTime as the currentTime to then get the time passed since the last frame
	lastTime = CurrentTime;

	// Increase the frame counter
	++framesPerSecond;

	// Now we want to subtract the current time by the start time that was stored.  If it is greater than 1
	// that means a second has passed and we need to display the new frame rate.  The 1.0 represents 1 second.  
	// Let's say we got 12031 (12.031) from GetTime() for the CurrentTime, and the startTime had 11230 (11.230).  
	// Well, 12.031 - 11.230 = 0.801, which is NOT a full second.  So we try again the next frame.  Once the 
	// CurrentTime - startTime comes out to be > 1 second, we calculate the frames for this last second.
	if (CurrentTime - startTime > 1.0f)
	{
		// Here we set the startTime to the currentTime.  This will be used as the starting point for the next second.
		// This is because GetTime() counts up, so we need to create a delta that subtract the current time from.
		startTime = CurrentTime;

		// Show the frames per second in the console window if desired
		if (writeToConsole)
			fprintf(stderr, "Current Frames Per Second: %d\n", int(framesPerSecond));

		// Store the current FPS since we reset it down below and need to store it to return it
		currentFPS = framesPerSecond;

		// Reset the frames per second
		framesPerSecond = 0;
	}

	// Return the most recent FPS
	return currentFPS;
}
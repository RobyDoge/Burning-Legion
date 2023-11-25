#pragma once
#include <chrono>

/*
This class has 2 main functionalities, getting the elapsed time and the delta time(when and if we will need to work with frames/second)
The elapsed time works by getting a new current time at every call, and substracting that from the start time (first reset).
It can be made slower or faster (if we want the time to go 2x faster for example ) using the timeScale variable.
See how it can be used in main
*/

class __declspec(dllexport) Timer
{
public:
	Timer();														 //Constructor
	~Timer();														 //Destructor

	float GetDeltaTime();											 //Calculate the time difference between frames
	float GetElapsedTime() const;								     //Get the total elapsed time since the timer started
	float GetTimeScale() const;										 //Get the time scale for the timer
	void  SetTimeScale(float timeScale);								 //Set the time scale for the timer


	void Reset();													 //Resets all variables to the time point when the method was called

private:
	std::chrono::high_resolution_clock::time_point m_startTime;		 // Time point when the Timer started
	std::chrono::high_resolution_clock::time_point m_lastTick;		 // Time point of the last frame
	std::chrono::high_resolution_clock::time_point m_currentTime;    // Current time point
	std::chrono::duration<float> m_deltaTime;						 // Time duration between frames
	float m_timeScale;												 // Scale to control the speed of time

};


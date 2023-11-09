#pragma once
#include <chrono>


class Timer
{
public:
	Timer();														 //Constructor
	~Timer();														 //Destructor
																	 
	float GetDeltaTime();											 //Calculate the time difference between frames
	float GetElapsedTime() const;								     //Get the total elapsed time since the timer started
	float GetTimeScale() const;										 //Get the time scale for the timer
	void SetTimeScale(float timeScale);								 //Set the time scale for the timer
	

	void Reset();

private:
	std::chrono::high_resolution_clock::time_point m_startTime;		 // Time point when the Timer started
	std::chrono::high_resolution_clock::time_point m_lastTick;		 // Time point of the last frame
	std::chrono::high_resolution_clock::time_point m_currentTime;    // Current time point
	std::chrono::duration<float> m_deltaTime;						 // Time duration between frames
	float m_timeScale;												 // Scale to control the time

};


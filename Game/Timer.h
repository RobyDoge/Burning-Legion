#pragma once
#include <chrono>
class Timer
{
private:
	std::chrono::high_resolution_clock::time_point m_startTime,m_lastTick,m_currentTime;
	std::chrono::duration<float> m_deltaTime;
	float m_timeScale;

public:

	Timer();
	~Timer();
	void Reset();
	float GetDeltaTime();
	float GetElapsedTime();
	void setTimeScale(float timeScale);
	float getTimeScale();

};


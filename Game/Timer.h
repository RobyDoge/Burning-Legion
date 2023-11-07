#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

	float GetDeltaTime();
	float GetElapsedTime() const;
	void SetTimeScale(float timeScale);
	float GetTimeScale() const;

	void Reset();

private:
	std::chrono::high_resolution_clock::time_point m_startTime;
	std::chrono::high_resolution_clock::time_point m_lastTick;
	std::chrono::high_resolution_clock::time_point m_currentTime;
	std::chrono::duration<float> m_deltaTime;
	float m_timeScale;


};


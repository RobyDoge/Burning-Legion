#pragma once
#include <chrono>
class Timer
{
private:
	std::chrono::system_clock::time_point m_startTime; 
	std::chrono::duration<float> m_deltaTime;
	float m_timeScale;

public:

	Timer();
	~Timer();
	void Reset();
	float GetDeltaTime();
	void SetTimeScale(float t = 1.0f);
	float GetTimeScale();
	void Tick();
	void CountDown(float countDowntime);

};


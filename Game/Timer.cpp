#include "Timer.h"


Timer::Timer() {
	Reset();
	m_startTime = m_lastTick = m_currentTime = std::chrono::high_resolution_clock::now();
	m_timeScale = 1.0f;
	m_deltaTime = std::chrono::duration<float>(0.0f);
}

void Timer::Reset() {
	m_startTime = std::chrono::high_resolution_clock::now();

}
float Timer::GetDeltaTime() {
	m_currentTime = std::chrono::high_resolution_clock::now();
	m_deltaTime = m_currentTime - m_lastTick;
	m_lastTick = m_currentTime;
	return m_deltaTime.count();
}

void Timer::setTimeScale(float timeScale)
{
	m_timeScale = timeScale;
}

float Timer::GetElapsedTime() {
	std::chrono::duration<float> elapsed_time = (std::chrono::high_resolution_clock::now() - m_startTime)*m_timeScale;
	return elapsed_time.count();
}

float Timer::getTimeScale()
{
	return m_timeScale;
}

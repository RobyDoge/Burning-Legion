#include "Timer.h"


Timer::Timer() {
	Reset();
	m_startTime= std::chrono::system_clock::now();
	m_timeScale = 1.0f;
	m_deltaTime = std::chrono::duration<float>(0.0f);
}

void Timer::Reset() {
	m_startTime = std::chrono::system_clock::now();

}
float Timer::GetDeltaTime() {
	return m_deltaTime.count();
}
void Timer::SetTimeScale(float t) {
	m_timeScale = t;
}

float Timer::GetTimeScale() {
	return m_timeScale;
}

void Timer::Tick() {
	m_deltaTime = (std::chrono::system_clock::now() - m_startTime)*m_timeScale;
}
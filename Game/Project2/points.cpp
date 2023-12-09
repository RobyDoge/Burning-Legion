module points;

import std;
import <cstdint>;

using server::Points;

Points::Points(const Points& other) :
	m_currentGamePoints{ other.m_currentGamePoints },
	m_turnPoints{ other.m_turnPoints },
	m_bestGamePoints{ other.m_bestGamePoints },
	m_lastMatchesPoints{ other.m_lastMatchesPoints }
{
}

Points& Points::operator=(const Points& other)
{
	Points tempPoints{ other };
	swap(tempPoints);
	return *this;
}

Points::Points(Points&& other) noexcept
{
	this->swap(other);
}

Points& Points::operator=(Points&& other) noexcept
{
	this->swap(other);
	return *this;
}

void Points::swap(Points& other) noexcept
{
	using std::exchange;
	m_bestGamePoints = exchange(other.m_bestGamePoints, m_bestGamePoints);
	m_currentGamePoints = exchange(other.m_currentGamePoints, m_currentGamePoints);
	m_turnPoints = exchange(other.m_turnPoints, m_turnPoints);
	m_lastMatchesPoints = exchange(other.m_lastMatchesPoints, m_lastMatchesPoints);
}

int16_t Points::GetCurrentGamePoints() const
{
	return m_currentGamePoints;
}

void Points::AddToCurrentGamePoints()
{
	m_currentGamePoints += m_turnPoints;
}

int16_t Points::GetTurnPoints() const
{
	return m_turnPoints;
}

int16_t Points::GetBestGamePoints() const
{
	return m_bestGamePoints;
}

std::deque<int16_t> Points::GetLastMatchesPoints() const
{
	return m_lastMatchesPoints;
}

void Points::SetBestGamePoints(const int16_t bestGamePoints)
{
	m_bestGamePoints = bestGamePoints;
}

void Points::SetLastMatchesPoints(const std::deque<int16_t>& lastMatchesPoints)
{
	m_lastMatchesPoints = lastMatchesPoints;
}


void Points::AddMatch()
{
	if (MAX_SIZE_OF_LAST_MATCHES == m_lastMatchesPoints.size())
	{
		m_lastMatchesPoints.pop_back();

	}
	m_lastMatchesPoints.emplace_front(m_currentGamePoints);
	if (m_currentGamePoints > m_bestGamePoints)
		m_bestGamePoints = m_currentGamePoints;

}

void Points::AddPointsGuesser(const float& time)
{
	if (static_cast<std::uint8_t>(time) < 30)
	{
		m_turnPoints = 100;
		return;
	}
	if (static_cast<std::uint8_t>(time) == 60)
	{
		m_turnPoints = -50;
		return;
	}
	m_turnPoints = (60 - static_cast<std::uint8_t>(time)) / 3 * 10;
}

void Points::AddPointsDrawer(const std::vector<float>& times)
{
	if (times.size() == 0)
	{
		m_turnPoints = -100;
		return;
	}
	float sum = 0;
	for (const auto& time : times)
	{
		sum += time;
	}
	m_turnPoints = (60 - static_cast<std::uint8_t>(sum / times.size())) / 3 * 5;
}

void server::swap(Points& first, Points& second) noexcept
{
	first.swap(second);
}

void Points::ResetTurnPoints()
{
	m_turnPoints = 0;
}

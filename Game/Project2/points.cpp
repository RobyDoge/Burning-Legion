module points;

import <deque>;
import <vector>;
import <cstdint>;

using game_logic::Points;

Points::Points(const Points& other) :
	m_gamePoints{ other.m_gamePoints },
	m_turnPoints{ other.m_turnPoints }
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
	m_gamePoints = exchange(other.m_gamePoints, m_gamePoints);
	m_turnPoints = exchange(other.m_turnPoints, m_turnPoints);

}

int16_t Points::GetCurrentGamePoints() const
{
	return m_gamePoints;
}

void Points::UpdateScore()
{
	m_gamePoints += m_turnPoints;
	m_turnPoints = 0;
}

int16_t Points::GetTurnPoints() const
{
	return m_turnPoints;
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

void game_logic::swap(Points& first, Points& second) noexcept
{
	first.swap(second);
}
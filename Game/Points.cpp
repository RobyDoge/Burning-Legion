import points;
import <cstdint>;
import <list>;
import <vector>;

using game::Points;

Points::Points():
	m_currentGamePoints{0},
	m_turnPoints{0},
	m_bestGamePoints{0}
{
}

Points::~Points() = default;

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

std::list<int16_t> Points::GetLastMatchesPoints() const
{
	return m_lastMatchesPoints;
}


void Points::AddMatch()
{
	if(MAX_SIZE_OF_LAST_MATCHES ==m_lastMatchesPoints.size())
	{
		m_lastMatchesPoints.pop_front();
		
	}
	m_lastMatchesPoints.emplace_back(m_currentGamePoints);
	if (m_currentGamePoints > m_bestGamePoints)
		m_bestGamePoints = m_currentGamePoints;

}

void Points::AddPointsGuesser(const float& time)
{
	if (static_cast<uint8_t>(time) < 30)
	{
		m_turnPoints = 100;
		return;
	}
	if (static_cast<uint8_t>(time) == 0)
	{
		m_turnPoints = -50;
		return;
	}
	m_turnPoints = (60 - static_cast<uint8_t>(time)) / 3 * 10;
}

void Points::AddPointsDrawer(const ::std::vector<float>& times)
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
	m_turnPoints = (60 - static_cast<uint8_t>(sum / times.size())) / 6 * 10;
}

void Points::ResetTurnPoints()
{
	m_turnPoints = 0;
}

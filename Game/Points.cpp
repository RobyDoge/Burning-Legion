import points;
#include <array>


using game::Points;

Points::Points()
{
	m_lastFiveMatchesPoints.fill(0);
	m_bestGamePoints = 0;
	m_currentGamePoints = 0;
	m_turnPoints = 0;
}

Points::Points(const Points& points)
{
	m_bestGamePoints = points.m_bestGamePoints;
	m_currentGamePoints = points.m_currentGamePoints;
	m_lastFiveMatchesPoints = points.m_lastFiveMatchesPoints;
	m_turnPoints = points.m_turnPoints;
}

Points::~Points() = default;

uint16_t Points::getCurrentGamePoints() const
{
	return m_currentGamePoints;
}

void Points::setCurrentGamePoints(const uint16_t currentGamePoints)
{
	m_currentGamePoints = currentGamePoints;
}

uint8_t Points::getTurnPoints() const
{
	return m_turnPoints;
}

void Points::setTurnPoints(const uint8_t turnPoints)
{
	m_turnPoints = turnPoints;
}

uint16_t Points::getBestGamePoints() const
{
	return m_bestGamePoints;
}

void Points::setBestGamePoints(const uint16_t bestGamePoints)
{
	m_bestGamePoints = bestGamePoints;
}

std::array<uint16_t, 5> Points::getLastFiveMatchesPoints() const
{
	return m_lastFiveMatchesPoints;
}

void Points::setLastFiveMatchesPoints(const std::array<uint16_t, 5>& lastFiveMatchesPoints)
{
	m_lastFiveMatchesPoints = lastFiveMatchesPoints;
}

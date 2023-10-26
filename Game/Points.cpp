#include "Points.h"

Points::Points()
{
	m_lastFiveMatchesPoints.fill(0);
}

Points::Points(const Points& points)
{
	m_bestGamePoints = points.m_bestGamePoints;
	m_currentGamePoints = points.m_currentGamePoints;
	m_lastFiveMatchesPoints = points.m_lastFiveMatchesPoints;
	m_turnPoints = points.m_turnPoints;

}

Points::~Points()
{
}


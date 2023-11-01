import points;

using game::Points;

Points::Points():
	m_currentGamePoints{0},
	m_turnPoints{0},
	m_bestGamePoints{0}
{
}

Points::Points(const Points& points)
{
	m_bestGamePoints = points.m_bestGamePoints;
	m_currentGamePoints = points.m_currentGamePoints;
	m_lastMatchesPoints = points.m_lastMatchesPoints;
	m_turnPoints = points.m_turnPoints;
}

Points::~Points() = default;

uint16_t Points::GetCurrentGamePoints() const
{
	return m_currentGamePoints;
}

void Points::SetCurrentGamePoints(const uint16_t currentGamePoints)
{
	m_currentGamePoints = currentGamePoints;
}

uint8_t Points::GetTurnPoints() const
{
	return m_turnPoints;
}

void Points::SetTurnPoints(const uint8_t turnPoints)
{
	m_turnPoints = turnPoints;
}

uint16_t Points::GetBestGamePoints() const
{
	return m_bestGamePoints;
}

void Points::SetBestGamePoints(const uint16_t bestGamePoints)
{
	m_bestGamePoints = bestGamePoints;
}

std::list<uint16_t> Points::GetLastMatchesPoints() const
{
	return m_lastMatchesPoints;
}

void Points::SetLastMatchesPoints(const std::list<uint16_t>& lastMatchesPoints)
{
	m_lastMatchesPoints = lastMatchesPoints;
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

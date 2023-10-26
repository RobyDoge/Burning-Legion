#pragma once
#include <cstdint>
#include <array>
class Points
{
public:
	Points();											//default constructor
	Points(const Points& points);						//copy constructor
	~Points();											//deconstructor


private:
	uint16_t m_currentGamePoints;						//the points earned in the current game 
	uint8_t m_turnPoints;								//temporary points earned during a turn
	uint16_t m_bestGamePoints;							//stores the best score ever obtained
	std::array<uint16_t,5> m_lastFiveMatchesPoints;		//an array that shows the points obtained in the last 5 mathes

};


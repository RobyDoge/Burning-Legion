export module points;
import <cstdint>;
import <array>;

namespace game
{
	export class Points
	{
	public:
		Points();											//default constructor
		Points(const Points& points);						//copy constructor
		~Points();											//destructor

		uint16_t getCurrentGamePoints() const;
		void setCurrentGamePoints(const uint16_t currentGamePoints);
		uint8_t getTurnPoints() const;
		void setTurnPoints(const uint8_t turnPoints);
		uint16_t getBestGamePoints() const;
		void setBestGamePoints(const uint16_t bestGamePoints);
		std::array<uint16_t, 5> getLastFiveMatchesPoints() const;
		void setLastFiveMatchesPoints(const std::array<uint16_t, 5>& lastFiveMatchesPoints);

	private:
		uint16_t m_currentGamePoints;						//the points earned in the current game 
		uint8_t m_turnPoints;								//temporary points earned during a turn
		uint16_t m_bestGamePoints;							//stores the best score ever obtained
		std::array<uint16_t, 5> m_lastFiveMatchesPoints;	//an array that shows the points obtained in the last 5 matches

	};
}

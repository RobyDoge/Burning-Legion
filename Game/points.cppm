export module points;
import <cstdint>;
import <array>;
import <list>;

namespace game
{

	export class Points
	{
	private:
		
	public:
		Points();											//default constructor
		Points(const Points& points);						//copy constructor
		~Points();											//destructor

		uint16_t GetCurrentGamePoints() const;
		void SetCurrentGamePoints(const uint16_t currentGamePoints);
		uint8_t GetTurnPoints() const;
		void SetTurnPoints(const uint8_t turnPoints);
		uint16_t GetBestGamePoints() const;
		void SetBestGamePoints(const uint16_t bestGamePoints);
		std::list<uint16_t> GetLastMatchesPoints() const;
		void SetLastMatchesPoints(const std::list<uint16_t>& lastMatchesPoints);

		void AddMatch();									/*adds the score of the game to the list and 
																checks if the score is bigger tge the all time best*/


	private:

		uint16_t m_currentGamePoints;							//the points earned in the current game 
		uint8_t m_turnPoints;									//temporary points earned during a turn
		uint16_t m_bestGamePoints;								//stores the best score ever obtained
		static constexpr uint8_t MAX_SIZE_OF_LAST_MATCHES  = 5;	//the size of the lastMatches array
		std::list<uint16_t> m_lastMatchesPoints;				//stores last matches points gained
	};
}

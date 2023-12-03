export module points;
import <cstdint>;
import <list>;
import <type_traits>;
import <vector>;

namespace server
{

	export class Points
	{
	public:
		Points();												//default constructor
		~Points();												//destructor
		Points(const Points& other);							//copy constructor
		Points& operator=(const Points& other);					//operator= for copy
		Points(Points&& other) noexcept;						//move constructor
		Points& operator=(Points&& other) noexcept;				//operator= for move 
		void Swap(Points& other) noexcept;						//swap for copy and move operators

		int16_t GetCurrentGamePoints() const;					//getter for currentGamePoints
		int16_t GetTurnPoints() const;							//getter for turnPoints
		int16_t GetBestGamePoints() const;						//getter for bestGamePoints
		std::list<int16_t> GetLastMatchesPoints() const;		//getter for lastMatchesPoints

		//if T is float, then we use the first method to get the score based on the score
		//if T is a vector we use the second method
		template <typename T>
		void SetTurnPoints(const T& time);
		void SetBestGamePoints(const int16_t bestGamePoints);
		void SetLastMatchesPoints(const std::list<int16_t>& lastMatchesPoints);
		void ResetTurnPoints();									//sets the turnPoints to 0
		void AddToCurrentGamePoints();							//adds the points obtain during a turn to the currentGamePoints
		void AddMatch();										//adds the score of the game to the list and checks if the score is bigger then the all time best						

	private:
		void AddPointsGuesser(const float& time);				//depending on the time taken to guess this calculates the points
		void AddPointsDrawer(const std::vector<float>& times);	//based on the average time of guessing of all the other players this calculates the points for the drawer
		

		int16_t m_currentGamePoints;							//the points earned in the current game 
		int16_t m_turnPoints;									//temporary points earned during a turn
		int16_t m_bestGamePoints;								//stores the best score ever obtained
		static constexpr uint8_t MAX_SIZE_OF_LAST_MATCHES  = 5;	//the size of the lastMatches array
		std::list<int16_t> m_lastMatchesPoints;					//stores last matches points gained
	};

	export template <typename T>
	void Points::SetTurnPoints(const T& time)
	{
		
		if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>)
		{
			AddPointsGuesser(time);
			return;
		}
		if constexpr (std::is_same_v<T, std::vector<float>>)
		{
			AddPointsDrawer(time);
		}
	}
}

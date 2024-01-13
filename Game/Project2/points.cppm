export module points;

import <type_traits>;
import <deque>;
import <vector>;
import <cstdint>;

namespace game_logic
{

	export class Points
	{
	public:
		Points() = default;										//default constructor
		~Points() = default;									//destructor

		Points(const Points& other);							//copy constructor
		Points& operator=(const Points& other);					//operator= for copy
		Points(Points&& other) noexcept;						//move constructor
		Points& operator=(Points&& other) noexcept;				//operator= for move 
		void swap(Points& other) noexcept;						//swap for copy and move operators

		//if T is float, then we use the first method to get the score based on the score
		//if T is a vector we use the second method
		template <typename T>
		void AddToTurnPoints(const T& time);				//sets the turnPoints based on the time taken to guess the word
		void UpdateGamePoints();							//adds the points obtain during a turn to the currentGamePoints

		int16_t GetCurrentGamePoints() const;					//getter for currentGamePoints
		int16_t GetTurnPoints() const;							//getter for turnPoints

	private:
		void AddPointsGuesser(const float& time);				//depending on the time taken to guess this calculates the points
		void AddPointsDrawer(const std::vector<float>& times);	//based on the average time of guessing of all the other players this calculates the points for the drawer

	private:
		static constexpr uint8_t MAX_SIZE_OF_LAST_MATCHES{ 5 };	//the size of the lastMatches array

	private:
		int16_t m_gamePoints{};							//the points earned in the current game 
		int16_t m_turnPoints{};									//temporary points earned during a turn
	};

	export template <>
	void Points::AddToTurnPoints<float>(const float& time)
	{
		AddPointsGuesser(time);
	}
	export template <>
	void Points::AddToTurnPoints<std::vector<float>>(const std::vector<float>& time)
	{
		AddPointsDrawer(time);
	}

	export void swap(Points& first, Points& second) noexcept;		//overload std::swap for two Player objects;
}

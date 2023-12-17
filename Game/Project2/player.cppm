export module user;
export import points;

import <string>;

namespace game_logic
{
	export class Player
	{
	public:
		Player();												//default constructor
		~Player();											//destructor

		Player(const Player& other);							//copy constructor
		Player& operator=(const Player& other);					//operator= for copy
		Player(Player&& other) noexcept;						//move constructor
		Player& operator=(Player&& other) noexcept;				//operator= for move 
		void swap(Player& other) noexcept;					//swap for copy and move  operators

		void SetName(const std::string& name);				//Sets m_name
		void SetPoints(const Points& points);				//Sets m_points
		std::string GetName() const;						//returns m_name
		Points& GetPoints();								//returns m_points


	private:
		std::string m_name{};								//the name and display name of a user
		Points m_points{};									//an object for storing different type of points
	};

	export void swap(Player& first, Player& second) noexcept;		//overload std::swap for two Player objects;
}
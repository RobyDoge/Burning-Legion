export module game;


import user;
import round;

import <cstdint>;
import <vector>;
import <string>;
import <queue>;

namespace server
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t ROUND = 4;										//the number of rounds

	public:
		enum class Difficulty : uint8_t				//difficulty for the game
		{
			Easy = 0b00,			
			Medium = 0b01,
			Hard = 0b10
		};																		
	public:
		Game() = default;														//default constructor
		~Game() = default;														//destructor

		void SetDifficulty(const Difficulty difficulty);						//sets the game difficulty at the start of the game
		Difficulty GetDifficulty() const;										//for checking the difficulty

		void AddPlayer(const User& newPlayer);									//adds players to m_player
		std::queue<std::string>& GenerateNextWords();							//generates a random number of words based on the number of players

		void StartGame();

	private:
		std::queue<std::string> m_currentWordList;								//the needed words for the game

	private:
		std::vector <User> m_players;											//vector storing players
		Difficulty m_difficulty;												//game difficulty
	};
}
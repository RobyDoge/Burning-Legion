export module game;

import user;
import round;

import <cstdint>;
import <vector>;
import <string>;

namespace server
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		enum class Difficulty
		{
			Easy,
			Medium,
			Hard
		};																		//game 'modes'

		Game() = default;														//default constructor
		~Game() = default;														//destructor

		void SetDifficulty(const Difficulty difficulty);						//sets the game difficulty at the start of the game
		Difficulty GetDifficulty() const;										//for checking the difficulty

		void AddPlayer(const User& newPlayer);									//adds players to m_player
		std::vector<std::string>& GenerateNextWords();

		void StartGame();

	private:
		std::vector<std::string> m_currentWordList;								//the needed words for the game
		static constexpr uint8_t ROUND = 4;										//the number of rounds
		std::vector <User> m_players;											//vector storing players
		Difficulty m_difficulty;												//game difficulty
	};
}
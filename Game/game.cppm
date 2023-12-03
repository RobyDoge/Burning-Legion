export module game;
import user;
import round;
import lobby;

import <cstdint>;
import std;

namespace server
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t NUMBER_OF_ROUNDS = 4;										//the number of rounds
	public:
		Game() = default;														//default constructor
		~Game() = default;														//destructor
		void Start(std::vector<User>& players,const Lobby::GameDifficulty difficulty);
		std::queue<std::string>& GenerateNextWords();							//generates a random number of words based on the number of players

	private:
		void CreateWordsForGame();
		std::queue<std::string> m_currentWordList;								//the needed words for the game
		void UpdateLastMatches(std::vector<User>& players);
	private:
		uint8_t m_numberOfPlayers;											//vector storing players
		Lobby::GameDifficulty m_difficulty;										//game difficulty
	};
}
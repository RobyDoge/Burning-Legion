export module game;
import user;
//import round;
//import lobby;

import <cstdint>;
//import std;
import <vector>;
import <queue>;
import <string>;
import <array>;
import <optional>;

namespace server
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t NUMBER_OF_ROUNDS = 4;							//the number of rounds
	public:
		Game() = default;														//default constructor
		~Game() = default;														//destructor
		//void Start(std::vector<User>& players,const Lobby::GameDifficulty difficulty);		//starts the turn 
		std::queue<std::string>& GenerateNextWords();							//generates a random number of words based on the number of players

	private:
		void CreateWordsForGame();												//from the word database populates currentWordList
		void UpdateLastMatches(std::vector<User>& players);						//after the game ends it updates the history for each player
		std::array<std::optional<User>, 3> Game::FindTheThreeWinners(std::vector<User>& players);		//return an array with up to top 3 players based on their score
	private:
		uint8_t m_numberOfPlayers;											//number of players
		//Lobby::GameDifficulty m_difficulty;									//game difficulty
		std::queue<std::string> m_currentWordList;								//the needed words for the game
	};
}
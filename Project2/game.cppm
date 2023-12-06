export module game;
import user;
import lobby;

import <queue>;

import <cstdint>;


namespace server
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t NUMBER_OF_ROUNDS = 4;							//the number of rounds

	public:
		Game() = default;														//default constructor
		~Game();																//destructor

		void Start(std::vector<User>& players, const Lobby::GameDifficulty difficulty);		//starts the turn with info from lobby
		std::queue<std::string>& GenerateNextWords();							//generates a random number of words based on the number of players


	private:
		void CreateWordsForGame();												//from the word database populates currentWordList
		void UpdateLastMatches();												//after the game ends it updates the history for each player
		std::list<User> FindTheThreeWinners();		//return an array with up to top 3 players based on their score

	private:
		std::queue<std::string> m_currentWordList;				//the needed words for the game
		Lobby::GameDifficulty m_difficulty;						//game difficulty
		std::vector<User> m_players;
	};
}
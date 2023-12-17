export module game;
import player;
import lobby;
import turn;

import <vector>;
import <queue>;
import <list>;
import <string>;
import <cstdint>;


namespace game_logic
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t NUMBER_OF_ROUNDS = 4;							//the number of rounds

	public:
		Game() = default;														//default constructor
		~Game() = default;														//destructor
		Game(std::vector<Player>& players, Lobby::GameDifficulty difficulty,Lobby::GameLanguage language);	//constructor with info from lobby)

		Turn GetTurn(uint8_t drawerPosition);									//returns the current turn
		std::string GetNextWord();							//generates a random number of words based on the number of players
		std::queue<Player> GetWinners();		//return an array with up to top 3 players based on their score

	private:

		void CreateWordsForGame(const Lobby::GameDifficulty difficulty, const Lobby::GameLanguage language);												//from the word database populates currentWordList
		void UpdateLastMatches();												//after the game ends it updates the history for each player
		

	private:
		std::vector<Player> m_players{};
		std::queue<std::string> m_currentWordList{};				//the needed words for the game
								
		

	};
}
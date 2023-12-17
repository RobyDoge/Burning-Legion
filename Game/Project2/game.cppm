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
		Game() = default;											//default constructor
		~Game()= default;													//destructor
		Game(std::vector<Player>& players, const std::queue<std::string>& words);	//constructor with info from lobby


		Turn GetTurn(uint8_t drawerPosition);	//returns the current turn
		std::string GetNextWord();				//generates a random number of words based on the number of players
		std::queue<Player> GetWinners();		//return an array with up to top 3 players based on their score
		void EndTurn(Turn& turn);				//ends the current turn
		void EndGame(std::vector<Player>& players);							//ends the game

	private:
		void UpdateScoreForAllPlayers();										//updates the score for all players
		

	private:
		std::vector<Player> m_players{};							//the players in the game
		std::queue<std::string> m_currentWordList{};				//the needed words for the game
								
		

	};
}
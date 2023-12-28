export module game;
import player;
import lobby;
import turn;

import <vector>;
import <queue>;
import <list>;
import <string>;
import <cstdint>;
import <memory>;

namespace game_logic
{
	//this class takes care of the game functionality
	export class Game
	{
	public:
		static constexpr uint8_t NUMBER_OF_ROUNDS = 4;							//the number of rounds

	public:
		enum class GameStatus : bool											//the status of the game
		{
			NotOver = false ,
			Over = true 
		};
	public:
		Game() = default;											//default constructor
		~Game()= default;													//destructor
		Game(std::vector<Player>& players, const std::queue<std::string>& words);	//constructor with info from lobby

		Turn GetTurn(uint8_t drawerPosition);	//returns the current turn
		std::string GetNextWord();				//generates a random number of words based on the number of players
		std::vector<Player> SortPlayersByTheirScore();		//return an array with up to top 3 players based on their score

		GameStatus GetGameStatus() const;		//returns the status of the game
		void SwitchGameStatus();				//switches the status of the game
		void EndTurn(std::shared_ptr<Turn> turn);				//ends the current turn
		void EndGame(std::vector<Player>& players);							//ends the game
		std::vector<Player>& GetPlayers();						//for checking the players

	private:
		void UpdateScoreForAllPlayers();										//updates the score for all players
		

	private:
		std::vector<Player> m_players{};							//the players in the game
		std::queue<std::string> m_currentWordList{};				//the needed words for the game
		GameStatus m_gameStatus{ GameStatus::NotOver };			//the status of the game
		

	};
}
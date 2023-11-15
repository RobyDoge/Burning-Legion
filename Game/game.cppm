export module game;
//#include "WordDatabase.h"
import <cstdint>;
import <vector>;
import <string>;
import user; 

namespace server
{
	export class Game
	{
	public:
		Game() = default;														//default constructor
		~Game() = default;														//destructor



		void AddPlayer(const User& newPlayer);									//adds players to m_player
		//void GenerateCurrentWordList(Dictionary& database);					//generates the words needed for the game from the word list

	private:
		std::vector<std::string> m_currentWordList;								//the needed words for the game
		static constexpr uint8_t ROUND = 4;										//the number of rounds
		std::vector <User> m_players;											//vector storing players
		enum class Difficulty
		{
			Easy,
			Medium,
			Hard
		};

	};
}
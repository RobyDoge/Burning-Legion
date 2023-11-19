export module round;
import user;
//import game;
import <vector>;
import <string>;

namespace server
{
	//this class gets from Game a vector of the users and the words necessary for a round
	export class Round
	{
	public:
		enum class Role : uint8_t													//enum defining different roles for players in a round
		{
			Drawer,				// player drawing the word
			Guesser,			// player guessing the word
			Finished,			// player that guessed the word
			NoRole				// for creating m_player at the begining
		};

		Round(std::vector<User>& players, const std::vector<std::string>& wordList);  //default constructor 
		void StartRound();															  //function to start the round

	private:
		void SetRoleForEachPlayer(const uint8_t drawerPosition);						//assigns roles to players
		void UpdateGamePoints();														//updates the game points



		std::vector<std::pair<User, Role>> m_players;									//vector storing the players
		std::vector<std::string> m_wordList;											//vector storing the words for the round
		uint8_t m_numberOfTurns;														//number of turns(players) for the round			
		
	};
}
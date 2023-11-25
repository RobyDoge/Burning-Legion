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
		enum class Role : uint8_t												//enum defining different roles for players in a round
		{
			Drawer = 0b00,					// player drawing the word
			Guesser = 0b01,					// player guessing the word
			Finished = 0b10,				// player that guessed the word
			NoRole= 0b11					// for creating m_player at the beginning
		};

	public:
		Round() = default;																			//default constructor 
		void StartRound(std::vector<User>& players, std::vector<std::string>& wordList);		//function to start the round


	private:
		enum class MoveDirection : bool
		{
			FromGameToRound,
			FromRoundToGame
		};

	private:
		void SetRoleForEachPlayer(uint8_t drawerPosition);								//assigns roles to players
		void UpdateGamePoints();														//updates the game points
		void Move(std::vector<User>& players, MoveDirection moveDirection);
		void CheckWordListSize() const;

	private:
		std::vector<std::string> m_wordList;
		std::vector<std::pair<User, Role>> m_players;									//vector storing the players
		uint8_t m_numberOfTurns;														//number of turns(players) for the round			
		
	};
}

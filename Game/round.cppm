export module round;
import user;
import std;
import <cstdint>;


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
		Round() = default;																	//default constructor 
		void StartRound(std::vector<User>& players, std::queue<std::string>& wordList);		//function to start the round


	private:
		enum class MoveDirection : bool										//enum for knowing which way a move should be done
		{
			FromGameToRound,				//the information received from game are being moved to round
			FromRoundToGame					//the information from round are being moved to back to game
		};

	private:
		void SetRoleForEachPlayer(uint8_t drawerPosition);								//assigns roles to players
		void UpdateGamePoints();														//updates the game points
		void Move(std::vector<User>& players, const MoveDirection moveDirection);		//either moves the elements from the vector to the class of vice versa
		void CheckWordListSize(const std::queue<std::string>& wordList) const;			//Throws an error in case there are not enough words
		void BeginRound(std::queue<std::string>& wordList);								//creates a number of turns equal to the size of players and updates the score

	private:
		std::vector<std::pair<User, Role>> m_players;									//vector for the players and their roles
		uint8_t m_numberOfTurns{};														//number of turns(players) for the round			
	};
}

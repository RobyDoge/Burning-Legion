export module turn;
import round;
import user;
import <vector>;
import <string>;


namespace  server
{
	
	export class Turn
	{
	public:
		Turn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn);		//default constructor
		void StartTurn();																				//function to start the round

	private:
		std::vector<std::pair<User, Round::Role>> m_players;											//players participating in the turn and their roles
		std::string m_wordToBeDrawn;																	//the word assigned to the drawer
	};
}

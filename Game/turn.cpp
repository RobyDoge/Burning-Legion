module turn;
import user;
import round;
import <string>;
import <vector>;

using server::Turn;
using namespace server;



Turn::Turn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn)
	: m_players{ players },
	m_wordToBeDrawn{ wordToBeDrawn }
{
}

void Turn::StartTurn()
{
	
	m_players[0].first.GetPoints().SetTurnPoints(58.3);
}

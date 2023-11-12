import turn;
import user;
import <string>;
import <vector>;

using game::Turn;
using namespace game;

Turn::Turn(std::vector<std::pair<User, Round::Role>> players, const std::string& wordToBeDraw):
	m_players{players},
	m_wordToBeDrawn{wordToBeDraw}
{
}

void Turn::StartTurn()
{
	
}

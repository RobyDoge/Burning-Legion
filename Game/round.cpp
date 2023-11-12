import round;
import user;
import turn;
#include <vector>
#include <string>

using game::Round;
using namespace game;

Round::Round(std::vector<User>& players, const std::vector<std::string>& wordList):
	m_players{players},
	m_wordList{wordList}
{
	m_numberOfTurns = players.size();
}



void Round::StartRound()
{
	for(uint8_t iterator=0;iterator< m_numberOfTurns;iterator++)
	{

		Turn turn(SetRoleForEachPlayer(iterator), m_wordList[iterator]);
		turn.StartTurn();
	}
	UpdateGamePoints();
	//here we could create a method to show the game points but i don't know how to do it yet
}

std::vector<std::pair<User, Round::Role>>& Round::SetRoleForEachPlayer(const uint8_t drawerPosition) const
{
	std::vector<std::pair<User, Round::Role>> playersAndTheirRoles;
	for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
	{
		Role role;
		if(iterator==drawerPosition)
		{
			role = Round::Role::Drawer;
		}
		else
		{
			role = Round::Role::Guesser;
		}
		playersAndTheirRoles.emplace_back({ m_players[iterator],role });
	}
	return playersAndTheirRoles;
}

void Round::UpdateGamePoints()
{
	for(auto& player: m_players)
	{
		player.GetPoints().AddToCurrentGamePoints();
		player.GetPoints().ResetTurnPoints();
	}
}

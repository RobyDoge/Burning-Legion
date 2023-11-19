module round;
import user;
import turn;
import <vector>;
import <string>;

using server::Round;
using namespace server;



Round::Round(std::vector<User>& players, const std::vector<std::string>& wordList):
	m_wordList{wordList}
{
	for(auto& player:players)
	{
		m_players.push_back({ player,Role::NoRole });
	}
	m_numberOfTurns = players.size();
}



void Round::StartRound()
{
	if(m_players.size() > m_wordList.size())
	{
		throw std::exception("Not Enough Words");
	}
	for(uint8_t iterator=0;iterator< m_numberOfTurns;iterator++)
	{
		SetRoleForEachPlayer(iterator);
		Turn turn(m_players, m_wordList[iterator]);
		turn.StartTurn();
	}
	UpdateGamePoints();
	//here we could create a method to show the game points but i don't know how to do it yet
}

void Round::SetRoleForEachPlayer(const uint8_t drawerPosition)
{
	for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
	{
		if (iterator == drawerPosition)
		{
			m_players[iterator].second = Role::Drawer;
			continue;
		}
		m_players[iterator].second = Role::Guesser;
	}
}

void Round::UpdateGamePoints()
{
	for(auto& player: m_players)
	{
		player.first.GetPoints().AddToCurrentGamePoints();
		player.first.GetPoints().ResetTurnPoints();
	}
}

module round;
import user;
import turn;
import <algorithm>;
import <vector>;
import <string>;

using server::Round;
using namespace server;


void Round::StartRound(std::vector<User>& players, std::queue<std::string>& wordList)
{
	Move(players, MoveDirection::FromGameToRound);
	m_wordList = std::move(wordList);
	m_numberOfTurns = m_players.size();
	CheckWordListSize();
	BeginRound();

	
	
	//here we could create a method to show the game points but i don't know how to do it yet

	Move(players, MoveDirection::FromRoundToGame);
}

void Round::BeginRound()
{
	for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
	{
		SetRoleForEachPlayer(iterator);
		Turn turn;
		turn.StartTurn(m_players, m_wordList.front());
		m_wordList.pop();
		UpdateGamePoints();
	}
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

void Round::CheckWordListSize() const
{
	if (m_players.size() > m_wordList.size())
	{
		throw std::exception("Not Enough Words");
	}
}


void Round::Move(std::vector<User>& players, MoveDirection moveDirection)
{
	if(moveDirection == MoveDirection::FromGameToRound)
	{
		m_players.clear();
		m_players.resize(players.size());
		std::transform(
			players.begin(),
			players.end(),
			m_players.begin(),
			[](User& user)
			{
				return std::make_pair(std::move(user), Role::NoRole);
			}
		);
		players.clear();
		return;
	}
	players.resize(m_players.size());
	std::transform(
		m_players.begin(),
		m_players.end(),
		players.begin(),
		[](const std::pair<User&, Role> pair)
		{
		return std::move(pair.first);
		}
	);
}

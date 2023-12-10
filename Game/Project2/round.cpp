module round;
import user;
import turn;

import <vector>;
import <queue>;
import <string>;

using namespace server;

void Round::StartRound(std::vector<User>& players, std::queue<std::string>& wordList)
{
	Move(players, MoveDirection::FromGameToRound);
	m_numberOfTurns = m_players.size();
	CheckWordListSize(wordList);
	BeginRound(wordList);

	//here we could create a method to show the game points but i don't know how to do it yet

	Move(players, MoveDirection::FromRoundToGame);
}

void Round::BeginRound(std::queue<std::string>& wordList)
{
	for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
	{
		SetRoleForEachPlayer(iterator);
		Turn turn{};
		turn.StartTurn(m_players, wordList.front());
		wordList.pop();
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
	/*for(auto& [user, role] : m_players)
	{
		user.GetPoints().AddToCurrentGamePoints();
		user.GetPoints().ResetTurnPoints();
	}*/
}

void Round::CheckWordListSize(const std::queue<std::string>& wordList) const
{
	if (m_players.size() > wordList.size())
	{
		//throw std::exception("Not Enough Words");
		//to add another wi to throw exception; i.e. new class fro each and verifying, to the end of the project;
	}
}


void Round::Move(std::vector<User>& players, const MoveDirection moveDirection)
{
	if (moveDirection == MoveDirection::FromGameToRound)
	{
		m_players.clear();
		m_players.resize(players.size());
		std::transform(
			players.begin(),
			players.end(),
			m_players.begin(),
			[](User& user)
			{
				return std::make_pair<User, Role>(std::move(user), Role::NoRole);
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

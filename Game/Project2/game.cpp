module game;
import turn;

import <vector>;
import <string>;
import <list>;
import <cstdint>;
import <ranges>;

using namespace game_logic;


Game::Game(std::vector<Player>& players, const std::queue<std::string>& words) 
{
	m_currentWordList = words;
	std::swap(m_players, players);
}

Turn Game::GetTurn(const uint8_t drawerPosition)
{
	Turn turn{m_players,m_currentWordList.front(),drawerPosition };
	m_currentWordList.pop();

	return turn;
}

std::string Game::GetNextWord()
{
	std::string wordsForRound{ m_currentWordList.front() };
	m_currentWordList.pop();
	return wordsForRound;
}

std::queue<Player> Game::GetWinners()		//return an array with up to top 3 players based on their score
{
	if (m_players.size() == 1)
	{
		return{m_players.begin(),m_players.begin()+1};
	}

	if (m_players.size() == 2)
	{

		if (m_players[0].GetPoints().GetCurrentGamePoints() > m_players[1].GetPoints().GetCurrentGamePoints())
		{
			return { m_players.begin(),m_players.begin() + 2};
		}
		return { m_players.rbegin().base(),m_players.rbegin().base() + 2};
	}

	std::vector<Player> playerCopy{ m_players };
	std::partial_sort(playerCopy.begin(), playerCopy.begin() + 3, playerCopy.end(), [](Player& first, Player& second)
		{
			return first.GetPoints().GetCurrentGamePoints() > second.GetPoints().GetCurrentGamePoints();
		});

	return { playerCopy.begin(),playerCopy.begin() + 3 };
}

void Game::EndTurn(Turn& turn)
{
	UpdateScoreForAllPlayers();
	turn.ReturnPlayers(m_players);
}

void game_logic::Game::EndGame(std::vector<Player>& players)
{
	std::swap(m_players, players);
}

void Game::UpdateScoreForAllPlayers()
{
	std::ranges::for_each(m_players, [](Player& player)
		{
			player.GetPoints().UpdateScore();
		});
}

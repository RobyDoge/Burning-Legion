module game;
import turn;

import <vector>;
import <string>;
import <list>;
import <cstdint>;
import <ranges>;
import <algorithm>;
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

std::vector<Player> Game::SortPlayersByTheirScore()
{
	std::vector<Player> playerCopy{ m_players };
	std::ranges::sort(playerCopy, [](Player& first, Player& second)
		{
			return first.GetPoints().GetCurrentGamePoints() > second.GetPoints().GetCurrentGamePoints();
		});

	return playerCopy;
}

Game::GameStatus Game::GetGameStatus() const
{
	return m_gameStatus;
}

void Game::SwitchGameStatus()
{
	m_gameStatus = static_cast<GameStatus>(!static_cast<bool>(m_gameStatus));
}

void Game::EndTurn(std::shared_ptr<Turn> turn)
{
	UpdateScoreForAllPlayers();
	turn->ReturnPlayers(m_players);
	if(turn->GetTurnStatus()==Turn::TurnStatus::NotOver)
	{
		turn->SwitchTurnStatus();
	}
}

void Game::EndGame(std::vector<Player>& players)
{
	std::swap(m_players, players);
	m_gameStatus = GameStatus::Over;
}

std::vector<Player>& Game::GetPlayers()
{
	return m_players;
}

void Game::UpdateScoreForAllPlayers()
{
	std::for_each(m_players.begin(),m_players.end(), [](Player& player)
		{
			player.GetPoints().UpdateScore();
		});
}

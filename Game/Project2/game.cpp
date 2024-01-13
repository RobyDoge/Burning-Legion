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

Turn Game::CreateTurn()
{
	return { m_players };
}

std::string Game::GetNextWord()
{
	std::string wordsForRound{ m_currentWordList.front() };
	m_currentWordList.pop();
	return std::move(wordsForRound);
}

std::vector<Player> Game::GetPlayersSortedByScore() const
{
	std::vector playerCopy{ m_players };
	std::ranges::sort(playerCopy, [](const Player& first, const Player& second)
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
	std::ranges::for_each(m_players, [](Player& player)
	{
		player.ChangePoints().UpdateGamePoints();
	});
}

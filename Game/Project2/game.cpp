module game;
import turn;

import <vector>;
import <string>;
import <list>;
import <cstdint>;

//#include "DatabaseHandlers.h"

using namespace game_logic;

Game::Game(std::vector<Player>& players, const Lobby::GameDifficulty difficulty, const Lobby::GameLanguage language):
	m_players{players}
{
	CreateWordsForGame(difficulty,language);
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

void Game::CreateWordsForGame(const Lobby::GameDifficulty difficulty, const Lobby::GameLanguage language)
{
	//m_currentWordList = WordDatabaseHandle::SelectWords(m_players.size() * NUMBER_OF_ROUNDS, m_difficulty);
}

void Game::UpdateLastMatches()
{
	for (auto& player : m_players)
	{
		player.GetPoints().AddMatch();
	}
}

std::queue<Player> Game::GetWinners()		//return an array with up to top 3 players based on their score
{

	if (m_players.size() == 1)
	{
		return { m_players[0] };
	}

	if (m_players.size() == 2)
	{

		if (m_players[0].GetPoints().GetCurrentGamePoints() > m_players[1].GetPoints().GetCurrentGamePoints())
		{
			return{ m_players[0],m_players[1] };
		}
		return { m_players[1],m_players[0] };
	}

	std::vector<Player> playerCopy{ m_players };
	std::partial_sort(playerCopy.begin(), playerCopy.begin() + 3, playerCopy.end(), [](Player& first, Player& second)
		{
			return first.GetPoints().GetCurrentGamePoints() > second.GetPoints().GetCurrentGamePoints();
		});

	return { playerCopy[0],playerCopy[1],playerCopy[2] };
}

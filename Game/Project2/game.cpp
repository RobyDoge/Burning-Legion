module game;
import round;

import <vector>;
import <string>;
import <list>;
import <cstdint>;

//#include "DatabaseHandlers.h"

using namespace game_logic;

void Game::Start(std::vector<User>& players, const Lobby::GameDifficulty difficulty /* limba*/)
{
	m_difficulty = difficulty;
	std::swap(m_players, players);
	CreateWordsForGame();
	//for (int i = 0; i <= NUMBER_OF_ROUNDS; i++)
	//{
	//	Round round{};
	//	round.StartRound(players, GenerateNextWords());
	//}

	//UpdateLastMatches();
	//auto topThreePlayers{ FindTheThreeWinners() };
	////de trimis catre game_logic castigatorii;
	//std::swap(players, m_players);
}

std::queue<std::string>& Game::GenerateNextWords()
{
	std::queue<std::string> wordsForRound{};
	for (int i = 0; i < m_players.size(); i++)
	{
		wordsForRound.push(m_currentWordList.front());
		m_currentWordList.pop();
	}
	return wordsForRound;
}

void Game::CreateWordsForGame()
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

std::list<User> Game::FindTheThreeWinners()
{

	if (m_players.size() == 1)
	{
		return { m_players[0] };
	}

	if (m_players.size() == 2)
	{

		if (m_players[0].GetPoints().GetLastMatchesPoints().front() > m_players[1].GetPoints().GetLastMatchesPoints().front())
		{
			return{ m_players[0],m_players[1] };
		}
		return { m_players[1],m_players[0] };
	}

	auto playerCopy{ m_players };
	std::partial_sort(playerCopy.begin(), playerCopy.begin() + 3, playerCopy.end(), [](User& first, User& second)
		{
			return first.GetPoints().GetLastMatchesPoints().front() > second.GetPoints().GetLastMatchesPoints().front();
		});

	return { playerCopy[0],playerCopy[1],playerCopy[2] };
}

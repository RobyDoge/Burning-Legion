module game;
import user;
import <vector>;
import <queue>;

#include "DatabaseHandlers.h"
using namespace server;

std::queue<std::string>& Game::GenerateNextWords()
{
	std::queue<std::string> wordsForRound;
	for(int i =0;i< m_numberOfPlayers;i++)
	{
		wordsForRound.push(m_currentWordList.front());
		m_currentWordList.pop();
	}
	return wordsForRound;
}

void server::Game::CreateWordsForGame()
{
	m_currentWordList = WordDatabaseHandle::SelectWords(m_numberOfPlayers * NUMBER_OF_ROUNDS, m_difficulty);
}

void Game::Start(std::vector<User>& players, const Lobby::GameDifficulty difficulty)
{
	m_difficulty = difficulty;
	m_numberOfPlayers = players.size();
	CreateWordsForGame();

	for(int i = 0;i<= NUMBER_OF_ROUNDS;i++)
	{
		Round round;
		round.StartRound(players, GenerateNextWords());
	}
	UpdateLastMatches(players);
	//signal for showing the winners;
}

void Game::UpdateLastMatches(std::vector<User>& players)
{
	for(auto& player : players)
	{
		player.GetPoints().AddMatch();
	}
}
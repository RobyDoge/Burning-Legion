#include "Game.h"

void Game::AddPlayer(const User& newPlayer)
{
	m_players.push_back(newPlayer);
}

void Game::GenerateCurrentWordList(WordList& baseWordList)
{
	uint8_t wordsNeeded = ROUND * m_players.size();
	while(wordsNeeded)
	{
		m_currentWordList.AddWord(baseWordList.GetRandomWord());
		--wordsNeeded;
	}
}

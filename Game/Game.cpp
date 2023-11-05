#include "Game.h"

void Game::AddPlayer(User newPlayer)
{
	m_players.push_back(newPlayer);
}

void Game::GenerateCurrentWordList(WordList& baseWordList)
{
	uint8_t wordsNeeded = TURNS * m_players.size();
	while(wordsNeeded)
	{
		wordsNeeded--;
		m_currentWordList.AddWord(baseWordList.GetRandomWord());
	}
}

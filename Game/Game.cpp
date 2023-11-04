#include "Game.h"

void Game::AddPlayer()
{
	m_players++;
}

void Game::generateCurrentWordList(WordList& baseWordList)
{
	uint8_t wordsNeeded = TURNS * m_players;
	while(wordsNeeded)
	{
		wordsNeeded--;
		m_currentWordList.AddWord(baseWordList.GetRandomWord());
	}
}

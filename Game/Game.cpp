#include "Game.h"
#include <sqlite_orm/sqlite_orm.h>

void Game::AddPlayer(const User& newPlayer)
{
	m_players.push_back(newPlayer);
}

void Game::GenerateCurrentWordList(Dictionary& database)
{
	uint8_t wordsNeeded = ROUND * m_players.size();
    //auto rows = database.limit(wordsNeeded).get_all<WordFromDictionary>();

    //for (const auto& row : rows)                // Add words from the database to the vector
    //{
    //   // m_currentWordList.push_back(row.word);
    //    wordsNeeded++;
    //}
}
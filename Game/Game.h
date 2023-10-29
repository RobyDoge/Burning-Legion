#pragma once

#include "Word.h"

class Game
{
private:
	std::vector<Word*> m_wordList;
public:
	Game();
	~Game();

	void generateWordList();
};


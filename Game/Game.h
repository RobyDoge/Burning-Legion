#pragma once

import word;
using game::Word;
import <vector>;

class Game
{
private:
	std::vector<Word*> m_wordList;
public:
	Game();
	~Game();

	void generateWordList();
};


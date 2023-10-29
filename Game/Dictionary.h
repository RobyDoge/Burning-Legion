#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Word.h"

class Dictionary
{
private:
	std::vector<std::pair < Word*, bool > > m_dictionary; //the boolean value checks if the word was already generated or not

public:
	Dictionary();
	~Dictionary();

	void readWordsFromFile(std::istream& wordList);
	void addWord(Word* newWord);

	Word* getRandomWord();
	void dictionaryReset();

};


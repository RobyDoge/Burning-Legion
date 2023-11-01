#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Word.h"

class Dictionary
{
public:
	Dictionary();
	~Dictionary();

	void ReadWordsFromFile(std::istream& wordList);
	void AddWord(Word* newWord);
	
	Word* GetRandomWord();
	void DictionaryReSet();


private:
	std::vector<std::pair < Word*, bool > > m_dictionary;	//the boolean value checks if the word was already generated or not


};


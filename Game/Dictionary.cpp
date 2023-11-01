#include "Dictionary.h"
#include <random>
#include <fstream>

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{
    for (auto& word : m_dictionary)
        delete word.first;

    m_dictionary.clear();
}

void Dictionary::ReadWordsFromFile(std::istream& wordList)
{
    Word currentWord;
    while (wordList >> currentWord)
    {
        Word* newWord = new Word(currentWord);
        AddWord(newWord);
    }
}

void Dictionary::AddWord(Word* newWord)
{
	const std::pair<Word*, bool> pair(newWord, false);
    m_dictionary.push_back(pair);
}

Word* Dictionary::GetRandomWord()
{
    if (m_dictionary.empty()) 
        return nullptr;

    srand(static_cast<unsigned>(time(nullptr)));

    const size_t randomIndex = rand() % m_dictionary.size();
    Word * randomWord = m_dictionary[randomIndex].first;
    m_dictionary[randomIndex].second = true;

    return randomWord;
}

void Dictionary::DictionaryReSet()
{
    for (auto& word : m_dictionary)
        word.second = false;
}

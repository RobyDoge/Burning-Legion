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

void Dictionary::readWordsFromFile(std::istream& wordList)
{
    Word currentWord;
    while (wordList >> currentWord)
    {
        Word* newWord = new Word(currentWord);
        addWord(newWord);
    }
}

void Dictionary::addWord(Word* newWord)
{
    std::pair<Word*, bool> pair(newWord, false);
    m_dictionary.push_back(pair);
}

Word* Dictionary::getRandomWord()
{
    if (m_dictionary.empty()) 
        return nullptr;

    srand(static_cast<unsigned>(time(0))); 

    size_t randomIndex = rand() % m_dictionary.size();
    Word * randomWord = m_dictionary[randomIndex].first;
    m_dictionary[randomIndex].second = true;

    return randomWord;
}

void Dictionary::dictionaryReset()
{
    for (auto& word : m_dictionary)
        word.second = false;
}

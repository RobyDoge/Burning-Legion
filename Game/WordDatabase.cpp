#include"WordDatabase.h"
#include<fstream>
#include<vector>
import utils;


void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    std::vector<WordFromDictionary> words;
    uint16_t idCounter = 1; 

    std::string word;
    uint8_t difficulty;
    while (inputFile >> word >> difficulty)
    {
       
        words.emplace_back(WordFromDictionary{ ++idCounter, word, difficulty });
    }

    dictionary.insert_range(words.begin(), words.end());
}

WordDatabase::WordDatabase(Dictionary& dictionary)
    : m_wordDatabase{ dictionary }
{
}

crow::response WordDatabase::operator()(const crow::request& req) const
{
    auto bodyArgs = ParseUrlArgs(req.body);
    auto end = bodyArgs.end();
    auto wordIter = bodyArgs.find("word");
    auto difficultyIter = bodyArgs.find("difficulty");

    if (wordIter != end && difficultyIter != end)
    {
        WordFromDictionary wordEntry;
        wordEntry.word = wordIter->second;
        wordEntry.difficulty = std::stoi(difficultyIter->second);
        m_wordDatabase.insert(wordEntry);
    }

    return crow::response(201); 
}


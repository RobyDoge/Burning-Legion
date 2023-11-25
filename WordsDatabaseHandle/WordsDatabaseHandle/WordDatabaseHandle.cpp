#include"WordDatabaseHandle.h"
#include<fstream>
#include<iostream>
#include<vector>

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
        words.emplace_back(WordFromDictionary{ idCounter++, word, difficulty });
    }

    dictionary.insert_range(words.begin(), words.end());
}



void WordDatabaseHandle::init()
{
    m_db.sync_schema();
    auto initalwordscount = m_db.count<WordFromDictionary>();
    if (initalwordscount == 0)
        PopulateDictionaryFromFile(m_db, "input.txt");

    auto initalwordscount2 = m_db.count<WordFromDictionary>();
    std::cout << initalwordscount2;
}

std::vector<std::string> WordDatabaseHandle::SelectWords(const uint8_t numberOfPlayers)
{
    std::vector<std::string> generatedWords;
    unsigned char difficulty = '1';
    uint8_t wordsNeeded = 4 * numberOfPlayers;
    //auto initalwordscount = db.count<WordFromDictionary>();
    auto rows = m_db.select(sqlite_orm::columns(&WordFromDictionary::word),
                          sqlite_orm::where(sqlite_orm::c( & WordFromDictionary::difficulty) == difficulty),
                          sqlite_orm::limit(wordsNeeded));
    
    
    for (const auto& row : rows)                // Add words from the database to the vector
    {
        generatedWords.push_back(std::get<0>(row));
    }
    return generatedWords;
}

#include"WordDatabase.h"
#include<fstream>
#include<iostream>
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

//void CreateDatabase()
//{
//    Dictionary db = CreateDictionary("words.sqlite");
//    db.sync_schema();
//    auto initalWordsCount = db.count<WordFromDictionary>();
//    if (initalWordsCount == 0)
//        PopulateDictionaryFromFile(db, "input.txt");
//}

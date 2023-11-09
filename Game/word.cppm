export module word;
import <string>;
import <unordered_set>;
import <fstream>;
import <random>;

namespace game 
{
    export class WordList
    {

    public:

        WordList() = default;											                //default constructor
        ~WordList() = default;                                                          //destructor

        void AddWord(const std::string& newWord);                                       //adds word to m_wordList
        std::string GetRandomWord();                                                    //gets random word from m_wordList

        friend std::istream& operator>>(std::istream& wordFile, WordList& wordList);    //reads words from stream

    private:
        std::unordered_set<std::string> m_wordList;                                     //the list of words (dictionary)
        std::default_random_engine m_randomEngine;                                      //used to generate random numbers for GetRandomWord
    };
    export std::istream& operator>>(std::istream& wordFile, WordList& wordList)
    {
        std::string newWord;
        while (wordFile >> newWord)
            wordList.AddWord(newWord);

        return wordFile;
    }
}
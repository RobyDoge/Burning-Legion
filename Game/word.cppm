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

        WordList() = default;
        ~WordList() = default;

        void AddWord(std::string newWord);
        std::string GetRandomWord();

        friend std::istream& operator >>(std::istream& wordFile, WordList& wordList);

    private:
        std::unordered_set<std::string> m_wordList;
        std::default_random_engine m_randomEngine;
    };

    export std::istream& operator>>(std::istream& wordFile, WordList& wordList)
    {
        std::string newWord;
        while (wordFile >> newWord)
            wordList.AddWord(newWord);

        return wordFile;
    }
}
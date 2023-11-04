export module word;
import <string>;
import <vector>;
import <fstream>;
import <ranges>;
import <algorithm>;

namespace game 
{
    export class WordList
    {

    public:

        WordList() = default;
        ~WordList() = default;

        void AddWord(std::string newWord);
        std::string GetRandomWord();

        friend std::istream& operator >>(std::istream& wordFile, const std::vector<std::string>& wordList);

    private:
        std::vector<std::string> m_wordList;
    };

}
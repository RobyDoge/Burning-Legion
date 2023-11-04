import word;
import <iostream>;
import <algorithm>;


using game::WordList;

void WordList::AddWord(std::string newWord)
{
    m_wordList.emplace_back(newWord);
}

std::istream& operator>>(std::istream& wordFile, WordList& wordList)
{
    std::string newWord;
    while (wordFile >> newWord)
        wordList.AddWord(newWord);

    //std::sort(wordList.begin(), wordList.end());
    return wordFile;
}

import word;
import <iostream>;
import <algorithm>;
import <random>;
import <ctime>;


using game::WordList;

void game::WordList::AddWord(std::string newWord)
{
    m_wordList.emplace_back(newWord);
}

std::string game::WordList::GetRandomWord()
{
    std::string newRandom;
    if (m_wordList.empty())
        return ""; // to add try...catch
    std::uniform_int_distribution<> distribution(0, m_wordList.size() - 1);
    return m_wordList[distribution(m_randomEngine)];
}

import word;
import <iostream>;
import <random>;
import <ctime>;
import <vector>;


using game::WordList;

void game::WordList::AddWord(std::string newWord)
{
    m_wordList.insert(newWord);
}

std::string game::WordList::GetRandomWord()
{
    std::string newRandom;
    if (m_wordList.empty())
        return ""; // to add try...catch
    
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 m_randomEngine(seed);

    std::vector<std::string> wordVector(m_wordList.begin(), m_wordList.end());
    std::uniform_int_distribution<> distribution(0, wordVector.size() - 1);
    return wordVector[distribution(m_randomEngine)];
}
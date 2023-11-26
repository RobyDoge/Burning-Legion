module game;
import user;
import <vector>;
import <queue>;


using server::Game;
using namespace server;

void Game::SetDifficulty(const Difficulty difficulty)
{
	m_difficulty = difficulty;
}

Game::Difficulty Game::GetDifficulty() const
{
	return m_difficulty;
}


void Game::AddPlayer(const User& newPlayer)
{
	m_players.push_back(newPlayer);
}

std::queue<std::string>& Game::GenerateNextWords()
{
	std::queue<std::string> wordsForRound;
	for(int i =0;i< m_players.size();i++)
	{
		wordsForRound.push(m_currentWordList.front());
		m_currentWordList.pop();
	}
	return wordsForRound;
}

void Game::StartGame()
{
	for(int i = 0;i<= ROUND;i++)
	{
		Round round;
		round.StartRound(m_players, GenerateNextWords());
	}
	
}

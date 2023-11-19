module game;
using server::Game;
using namespace server;
import user;

void server::Game::SetDifficulty(const Difficulty difficulty)
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

std::vector<std::string> server::Game::GenerateNextWords()
{
	std::vector<std::string> wordsForRound;
	for(int i =0;i< m_players.size();i++)
	{
		wordsForRound.emplace_back(m_currentWordList[m_currentWordList.size() - 1]);
		m_currentWordList.pop_back();
	}
	return wordsForRound;
}

void Game::StartGame()
{
	for(int i = 0;i<= ROUND;i++)
	{
		Round round(m_players, GenerateNextWords());
		round.StartRound();
	}
	
}

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

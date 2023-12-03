module lobby;
import user;
import game;
//import std;
import <string>;
import <ctime>;
import <cstdlib>;

using namespace server;

Lobby::Lobby()
{
    GenerateIdLobby();
}

std::string Lobby::GetIdLobby() const
{
	return m_idLobby;
}

void Lobby::AddPlayer(const std::string& name, const uint16_t bestScore, const std::list<int16_t>& lastMatchesPoints)
{
    User newUser;
    newUser.SetName(name);
    Points newPoints;
    newPoints.SetBestGamePoints(bestScore);
    newPoints.SetLastMatchesPoints(lastMatchesPoints);
    newUser.SetPoints(newPoints);
    m_players.emplace_back(newUser);
}

void Lobby::GenerateIdLobby()
{
    const std::string charset{ 
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	};
	m_idLobby.reserve(ID_SIZE);
    srand(static_cast<unsigned int>(time(nullptr))); 
    for (int i = 0; i < ID_SIZE; ++i) 
    {
        m_idLobby += charset[rand() % charset.length()];
    }
}

void Lobby::StartGame()
{
    Game game{};
    //game.Start();
}

void Lobby::SetDifficulty(const GameDifficulty difficulty)
{
    m_difficulty = difficulty;
}

Lobby::GameDifficulty Lobby::GetDifficulty() const
{
    return m_difficulty;
}
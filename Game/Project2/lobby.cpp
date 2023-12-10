module lobby;
import user;

import <random>;
import <deque>;
import <string>;
import <string>;
import <cstdint>;

using namespace server;

Lobby::Lobby()
{
    //GenerateIdLobby();
}

std::string Lobby::GetIdLobby() const
{

    return m_idLobby;
}

std::vector<User>& Lobby::GetPlayers()
{
    return m_players;
}

void Lobby::AddPlayer(const std::string& name, const uint16_t bestScore, const std::deque<int16_t>& lastMatchesPoints)
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, charset.length() - 1);
    for (int i = 0; i < ID_SIZE; ++i)
    {
        const int randomIndex = charset[distr(gen)];
        m_idLobby.push_back(charset[randomIndex]);
    }

}

void Lobby::SetDifficulty(const uint8_t difficulty)
{
    switch (difficulty)
    {
    case 1:
        m_difficulty = GameDifficulty::Easy;
        return;
    case 2:
        m_difficulty = GameDifficulty::Medium;
        return;
    case 3:
        m_difficulty = GameDifficulty::Hard;
        return;
    default:
        m_difficulty = GameDifficulty::NoDifficulty;
    }
    
}

Lobby::GameDifficulty Lobby::GetDifficulty() const
{
    return m_difficulty;
}
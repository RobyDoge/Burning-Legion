module lobby;
import Player;

import <random>;
import <deque>;
import <string>;
import <string>;
import <cstdint>;

using namespace game_logic;

std::vector<Player>& Lobby::GetPlayers()
{
    return m_players;
}

void Lobby::AddPlayer(const std::string& name)
{
    Player newUser{};
    newUser.SetName(name);
    const Points newPoints{};
    newUser.SetPoints(newPoints);
    m_players.emplace_back(newUser);
}

void Lobby::RemovePlayer(const std::string& name)
{
    auto playerToBeDeleted = std::ranges::find(m_players, name);
    if (playerToBeDeleted == m_players.end())
    {
        //TODO: throw exception
        return;
    }
    m_players.erase(playerToBeDeleted);
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

Lobby::GameLanguage Lobby::GetLanguage() const
{
    return m_language;
}

void Lobby::SetLanguage(const uint8_t language)
{
    switch (language)
    {
    case 1:
       m_language = GameLanguage::Romanian;
        return;
    case 2:
        m_language = GameLanguage::Spanish;
        return;
    default:
        m_language = GameLanguage::English;
    }
}

Lobby::GameDifficulty Lobby::GetDifficulty() const
{
    return m_difficulty;
}


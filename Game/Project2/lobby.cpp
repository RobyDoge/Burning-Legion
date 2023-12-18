﻿module lobby;
import player;

import <string>;
import <string>;
import <cstdint>;

using namespace game_logic;

std::vector<Player>& Lobby::GetPlayers()
{
    return m_players;
}

std::vector<std::string>& Lobby::GetUsersNames()
{
	return m_usersNames;
}

void Lobby::AddPlayer(const std::string& name)
{
    Player newUser{};
    newUser.SetName(name);
    const Points newPoints{};
    newUser.SetPoints(newPoints);
    m_players.emplace_back(newUser);
    m_usersNames.push_back(name);

}

void Lobby::RemovePlayer(const std::string& name)
{
    auto playerToBeDeleted = std::ranges::find_if(m_players, [&name](const Player& player) { return player.GetName() == name; });
    if (playerToBeDeleted == m_players.end())
    {
        //TODO: throw exception
        return;
    }
    m_players.erase(playerToBeDeleted);
	m_usersNames.erase(std::remove(m_usersNames.begin(), m_usersNames.end(), name), m_usersNames.end());
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

uint8_t Lobby::GetLanguage() const
{
    return static_cast<uint8_t>(m_language);
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

uint8_t Lobby::GetDifficulty() const
{
    return static_cast<uint8_t>(m_difficulty);
}


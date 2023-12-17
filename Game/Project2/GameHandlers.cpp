#include "GameHandlers.h"
import turn;

using game_logic::Turn;
using game_logic::Game;
using game_logic::Lobby;
using server::GameHandlers;

GameHandlers::~GameHandlers()
{
	m_lobby.reset();
	m_game.reset();
}

void GameHandlers::CreateLobby()
{
	m_lobby = std::make_unique<Lobby>();
}

void GameHandlers::AddUserToLobby(const std::string& username)
{
	m_lobby->AddUser(username);
}

void GameHandlers::RemoveUserFromLobby(const std::string& username)
{
	m_lobby->RemoveUser(username);
}

void GameHandlers::SetDifficulty(int difficulty)
{
	m_lobby->SetDifficulty(difficulty);
}

void GameHandlers::SetLanguage(int language)
{
	m_lobby->SetLanguage(language);
}

void GameHandlers::StartGame()
{
	m_game = std::make_unique<Game>(m_lobby->GetUsers(), m_lobby->GetDifficulty(), m_lobby->GetLanguage());

}



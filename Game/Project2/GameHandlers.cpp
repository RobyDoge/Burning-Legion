import turn;
import game;
import lobby;

#include "GameHandlers.h"
#include "Timer.h"

using namespace game_logic;
using server::GameHandlers;

void GameHandlers::CreateLobby()
{
	m_lobby = std::make_unique<Lobby>();
}

void GameHandlers::AddUserToLobby(const std::string& username)
{
	m_lobby->AddPlayer(username);
}

void GameHandlers::RemoveUserFromLobby(const std::string& username)
{
	m_lobby->RemovePlayer(username);
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
	m_game = std::make_unique<Game>(m_lobby->GetPlayers(), m_lobby->GetDifficulty(), m_lobby->GetLanguage());
	for(uint8_t _{};_<m_game->NUMBER_OF_ROUNDS;_++)
	{
		for(uint8_t drawerPosition{};drawerPosition<m_lobby->GetPlayers().size();drawerPosition++)
		{
			Turn turn{ m_game->GetTurn(drawerPosition) };
			Timer timer{};
			uint8_t secondsPassed{};
			uint8_t ticksPassed{};
			std::string wordToBeGuessed{ m_game->GetNextWord() };


			//TODO: Send Word Censored To Be Guessed To Clients (except drawer) And Send Uncensored Word To Drawer

			timer.Reset();
			while(true && secondsPassed< turn.TURN_LIMIT)
			{
				//TODO: Receive TextBox Input From Clients And Analyze It

				if(timer.GetElapsedTime()>0.1)
				{
					ticksPassed++;

					//TODO: Send Last Received Drawing To Clients

					timer.Reset();
				}
				if(ticksPassed==10)
				{
					secondsPassed++;

					uint8_t currentTime{ static_cast<uint8_t>(turn.TURN_LIMIT - secondsPassed) };

					//TODO: Send Current Time To Clients

					ticksPassed=0;
				}
			}
			m_game->EndTurn(turn);
			//TODO: Send Score To Clients
			//TODO: Save The Drawing
		}
	}

	auto winners{ m_game->GetWinners() };
	//TODO: Send Winners To Clients

	m_game->EndGame(m_lobby->GetPlayers());
}



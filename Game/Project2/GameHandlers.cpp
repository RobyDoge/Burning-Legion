import turn;
import game;
import lobby;

#include "GameHandlers.h"
#include "Timer.h"

using namespace game_logic;
using server::GameHandlers;

GameHandlers::~GameHandlers()
{
	m_lobby.reset();
}

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
			constexpr uint8_t MAX_TIME{ 60 };
			uint8_t secondsPassed{};
			uint8_t ticksPassed{};
			std::string wordToBeGuessed{ m_game->GetNextWord() };


			//TODO: Send Word Censored To Be Guessed To Clients (except drawer) And Send Uncensored Word To Drawer

			timer.Reset();
			while(true && secondsPassed<MAX_TIME)
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

					uint8_t currentTime{ static_cast<uint8_t>(MAX_TIME - secondsPassed) };

					//TODO: Send Current Time To Clients

					ticksPassed=0;
				}
			}

		}
	}

	auto winners{ m_game->GetWinners() };


}



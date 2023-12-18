import turn;
import game;
import lobby;

#include "GameHandlers.h"
#include "Timer.h"
#include "DatabaseHandlers.h"

using namespace game_logic;
using server::GameHandlers;

void GameHandlers::CreateLobby()
{
	m_lobby = std::make_unique<Lobby>();
}


void GameHandlers::AddUserToLobby(const std::string& username) const
{
	m_lobby->AddPlayer(username);
}

void GameHandlers::RemoveUserFromLobby(const std::string& username) const
{
	m_lobby->RemovePlayer(username);
}

std::vector<std::string> GameHandlers::GetUsersNames() const
{
	return m_lobby->GetUsersNames();
}

void GameHandlers::SetDifficulty(const int difficulty) const
{
	m_lobby->SetDifficulty(difficulty);
}

uint8_t GameHandlers::GetDifficulty()
{
	return m_lobby->GetDifficulty();
}

void GameHandlers::SetLanguage(const int language) const
{
	m_lobby->SetLanguage(language);
}


std::string GameHandlers::GetWordToBeGuessed()
{
	return m_wordToBeGuessed;
}

void GameHandlers::StartGame()
{
	m_game = std::make_unique<Game>(m_lobby->GetPlayers(), 
		CreateWordsNeeded(
			static_cast<uint8_t>(static_cast<uint8_t>(m_lobby->GetPlayers().size()) * m_game->NUMBER_OF_ROUNDS),
			m_lobby->GetDifficulty(), m_lobby->GetLanguage())
		);


	for(uint8_t _{};_<m_game->NUMBER_OF_ROUNDS;_++)
	{
		for(uint8_t drawerPosition{};drawerPosition<m_lobby->GetPlayers().size();drawerPosition++)
		{
			Turn turn{ m_game->GetTurn(drawerPosition) };
			Timer timer{};
			uint8_t secondsPassed{};
			uint8_t ticksPassed{};
			m_wordToBeGuessed = m_game->GetNextWord();


			//TODO: Send Word Censored To Be Guessed To Clients (except drawer) And Send Uncensored Word To Drawer

			timer.Reset();
			while(true && secondsPassed< turn.TURN_LIMIT)
			{
				//TODO: Receive TextBox Input From Clients And Analyze It,add points to the player who guessed the word

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

	//TODO: Update Database
}

std::queue<std::string> GameHandlers::CreateWordsNeeded(const uint8_t wordsNeeded,const uint8_t difficulty, const uint8_t language) const
{
	WordDatabaseHandle wordDbHandle;
	auto aux = wordDbHandle.SelectWords(wordsNeeded, difficulty, language);
	return aux;
}



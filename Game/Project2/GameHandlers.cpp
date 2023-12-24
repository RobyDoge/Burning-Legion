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

uint8_t GameHandlers::GetDifficulty() const
{
	return m_lobby->GetDifficulty();
}

void GameHandlers::SetLanguage(const int language) const
{
	m_lobby->SetLanguage(language);
}

uint8_t GameHandlers::GetLanguage() const
{
	return m_lobby->GetLanguage();
}

std::string GameHandlers::GetWordToBeGuessed()
{
	return m_wordToBeGuessed;
}

std::queue<std::string> GameHandlers::CreateWordsNeeded(const uint8_t wordsNeeded,const uint8_t difficulty, const uint8_t language) const
{
	WordDatabaseHandle wordDbHandle;
	if (!wordDbHandle.IsInitialized())
		wordDbHandle.Init();
	return wordDbHandle.SelectWords(wordsNeeded, difficulty, language);
	 
}


std::string GameHandlers::CheckMessage(const std::string& message) const
{
	return m_currentTurn->VerifyInputWord(m_wordToBeGuessed, message);

}

bool GameHandlers::GetGameStatus() const
{
	return static_cast<bool>(m_game->GetGameStatus());
}

bool GameHandlers::GetTurnStatus() const
{
	return static_cast<bool>(m_currentTurn->GetTurnStatus());
}


void GameHandlers::TurnThreadStart(uint8_t drawerPosition, uint8_t roundIndex)
{
	std::thread turnThread([this,drawerPosition, roundIndex]()
		{
			Turn turn{ m_game->GetTurn(drawerPosition) };
			m_currentTurn = std::make_shared<Turn>(turn);
			Timer timer{};
			uint8_t secondsPassed{};
			uint8_t ticksPassed{};
			m_wordToBeGuessed = m_game->GetNextWord();

			timer.Reset();
			while (true && secondsPassed < turn.TURN_LIMIT)
			{
				//add points to the player who guessed the word

				if (timer.GetElapsedTime() > 0.1)
				{
					++ticksPassed;

					//TODO: Send Last Received Drawing To Clients

					timer.Reset();
				}
				if (ticksPassed == 10)
				{
					++secondsPassed;

					uint8_t currentTime{ static_cast<uint8_t>(turn.TURN_LIMIT - secondsPassed) };

					//TODO: Send Current Time To Clients

					ticksPassed = 0;
				}
			}
			m_game->EndTurn(m_currentTurn);
			StartNextTurn(drawerPosition, roundIndex);

		});
	turnThread.detach();
}

void GameHandlers::StartNextTurn(uint8_t drawerPosition, uint8_t roundIndex)
{
	// TODO: Puteți adăuga aici logica specifică atunci când un tur se încheie

	// Verificați dacă mai sunt runde și jucători
	if (roundIndex < m_game->NUMBER_OF_ROUNDS - 1)
	{
			if (drawerPosition < m_game->GetPlayers().size() - 1)
			{
				// Programați următorul tur
				TurnThreadStart(drawerPosition + 1, roundIndex);
			}
			else
			{
				roundIndex++;
				drawerPosition = 0;
				TurnThreadStart(drawerPosition, roundIndex);
			}

	}
	else
	{
		auto winners{ m_game->GetWinners() };

		m_game->EndGame(m_game->GetPlayers());
	}
}

void GameHandlers::StartGame()
{
	m_game = std::make_unique<Game>(m_lobby->GetPlayers(), 
		CreateWordsNeeded(
			static_cast<uint8_t>(static_cast<uint8_t>(m_lobby->GetPlayers().size()) * m_game->NUMBER_OF_ROUNDS),
			m_lobby->GetDifficulty(), m_lobby->GetLanguage())
		);

	TurnThreadStart(0,0);		

}

import turn;
import game;
import lobby;

#include "GameHandlers.h"
#include "Timer.h"
#include "DatabaseHandlers.h"
#include <thread>

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

std::queue<std::string> GameHandlers::CreateWordsNeeded(const uint8_t wordsNeeded,const uint8_t difficulty, const uint8_t language)
{
	WordDatabaseHandle wordDbHandle;
	if (!wordDbHandle.IsInitialized())
		wordDbHandle.Init();
	return wordDbHandle.SelectWords(wordsNeeded, difficulty, language);
	 
}


std::string GameHandlers::CheckMessage(const std::string& message,const std::string& guesser) const
{
	const auto& guess {m_currentTurn->VerifyInputWord(m_wordToBeGuessed, message) };
	if (guess == "Correct Guess")
	{
		m_correctGuesses++;
		m_currentTurn->AddToGuessingTimes(m_currentTime, guesser);
	}
	return guess;

}

bool GameHandlers::GetGameStatus() const
{
	return static_cast<bool>(m_game->GetGameStatus());
}

bool GameHandlers::GetTurnStatus() const
{
	return static_cast<bool>(m_currentTurn->GetTurnStatus());
}

uint8_t GameHandlers::GetDrawerPosition() const
{
	return m_drawerPosition;
}

std::string GameHandlers::GetDrawerName() const
{
	return m_currentTurn->GetPlayers()[m_drawerPosition].GetName();	
}
int GameHandlers::GetTime() const
{
	return m_currentTime;
}
void server::GameHandlers::SetCurrentGuess(const std::string& guess)
{
	m_currentGuess = guess;
}
std::string GameHandlers::GetCurrentGuess() const
{
	return m_currentGuess;
}
std::string GameHandlers::GetDrawing() const
{
	return m_drawing;
}
void GameHandlers::SetDrawing(const std::string& drawing)
{
	m_drawing = drawing;
}

std::vector<std::pair<std::string, float>> GameHandlers::GetPlayersTurnPoints() const
{
	return m_currentTurnPoints;
}

std::vector<std::pair<std::string, float>> GameHandlers::GetPlayersGamePoints() const
{
	std::vector<std::pair<std::string, float>> playersGamePoints{};
	for(const auto& player : m_game->GetPlayers())
	{
		playersGamePoints.push_back({ player.GetName(), player.GetPoints().GetCurrentGamePoints() });
	}
	return playersGamePoints;
}

void GameHandlers::TurnThreadStart(uint8_t roundIndex)
{
	std::thread turnThread([this, roundIndex]()
		{
			Turn turn(m_game->CreateTurn(m_drawerPosition));
			m_currentTurn = std::make_shared<Turn>(turn);
			uint8_t secondsPassed{};
			uint8_t ticksPassed{};
			m_wordToBeGuessed = m_game->GetNextWord();
			m_correctGuesses = 0;
			m_currentTime = 0;
			m_timer.Reset();
			while (m_correctGuesses < m_currentTurn->GetPlayers().size()-1 && secondsPassed < m_currentTurn->TURN_LIMIT)
			{

				if (m_timer.GetElapsedTime() > 0.1)
				{
					++ticksPassed;
					m_timer.Reset();
				}
				if (ticksPassed == 10)
				{
					++secondsPassed;
					m_currentTime++;
					//uint8_t currentTime{ static_cast<uint8_t>(turn.TURN_LIMIT - secondsPassed) };
					ticksPassed = 0;
				}
			}
			
				m_currentTurn->FillGuessingTimes();

			m_currentTurnPoints = m_currentTurn->AddPointsForEachPlayer();
			m_game->EndTurn(m_currentTurn);
			
			StartNextTurn(roundIndex);

		});
	turnThread.detach();
}
void GameHandlers::StartNextTurn(uint8_t roundIndex)
{

	if (roundIndex < m_game->NUMBER_OF_ROUNDS - 1)
	{
			if (m_drawerPosition < m_game->GetPlayers().size() - 1)
			{
				m_drawerPosition++;
				m_timer.Reset();
				//turn points sent
				while (m_timer.GetElapsedTime() < 5)
				{
				}
				TurnThreadStart( roundIndex);
			}
			else
			{
				++roundIndex;
				m_drawerPosition = 0;
				m_timer.Reset();
				while (m_timer.GetElapsedTime() < 5)
				{
				}
				TurnThreadStart(roundIndex);
			}

	}
	else
	{
		auto winners{ m_game->GetPlayersSortedByScore() };

		m_game->EndGame(m_game->GetPlayers());
	}
}

bool GameHandlers::IsGameStarted() const
{
	return m_gameStarted;
}

void GameHandlers::StartGame()
{
	m_game = std::make_unique<Game>(m_lobby->GetPlayers(), 
		CreateWordsNeeded(
			static_cast<uint8_t>(static_cast<uint8_t>(m_lobby->GetPlayers().size()) * m_game->NUMBER_OF_ROUNDS),
			m_lobby->GetDifficulty(), m_lobby->GetLanguage())
		);
	m_gameStarted = true;
	m_drawerPosition = 0;
	TurnThreadStart(0);		

}

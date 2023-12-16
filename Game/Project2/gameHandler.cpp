#include "gameHandler.h"
import round;
import turn;
#include <queue>


using namespace server;

GameHandler::GameHandler() {}
GameHandler::~GameHandler() {}



void GameHandler::Start()
{

}



void server::GameHandler::AddUserToLobby(const std::string& username)
{
	m_currentLobby->AddPlayer(username, m_userStorage.GetBestScore(username), m_userStorage.GetLastMatchesPoints(username));
	m_currentPlayers.push_back(username);
}

void server::GameHandler::SetDifficuly(int difficulty)
{
	m_currentLobby->SetDifficulty(difficulty);
}

void server::GameHandler::SetWordToBeGuessed(std::string wordToBeGuessed)
{
	m_wordToBeGuessed = wordToBeGuessed;
}

std::string server::GameHandler::GetWordToBeGuessed()
{
	return m_wordToBeGuessed;
}

void server::GameHandler::StartGame()
{
	m_wordStorage.Init();
	auto nr = m_wordStorage.m_db.count<WordFromDictionary>();
	std::string s{ "eng" };
	std::queue<std::string> words = m_wordStorage.SelectWords(5, 48, s);
	while (true)
	{
		for (int i = 0; i <= m_game.NUMBER_OF_ROUNDS; i++)
		{
			Round round{};
			round.StartRound(m_currentLobby->GetPlayers(), m_game.GenerateNextWords()); //Functia asta de generate words nush exact ce face?
			for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
			{
				SetWordToBeGuessed(words.front());
				round.SetRoleForEachPlayer(iterator);
				Turn turn{};
				//turn.GuessingTimeVectorInitialization(players); -> Nu stiu ce face asta????
				m_timerTurn.Reset();
				m_timerServer.Reset();
				int countDown = 60;
				while (true && countDown != 0) {
					if (turn.VerifyInputWord(m_wordToBeGuessed, m_playerMessage).first == "guessed correctly")
					{
						break;
					}

					if (m_timerServer.GetElapsedTime() > 0.1)
					{
						//primeste si trimite desenul
						m_timerServer.Reset();
					}

					if (m_timerTurn.GetElapsedTime() > 1)
					{
						std::cout << countDown << "A trecut o secunda :D\n";
						countDown--;
						//sent countdown to client to update 
						m_timerTurn.Reset();
					}


				}

			}
		}
	}
}
void server::GameHandler::HandleLobby(const std::string& action, std::string lobbyId)
{
	if (action == "create") {
		m_currentLobby = new Lobby();
		m_currentLobby->GenerateIdLobby();
		m_lobbys.push_back(m_currentLobby);
	}
	else if (action == "join") {
		for (Lobby* lobby : m_lobbys) {
			if (lobby->GetIdLobby() == lobbyId)
				m_currentLobby = lobby;
		}
	}
}
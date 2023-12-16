import game;
import lobby;

#include "timer.h"
#include "DatabaseHandlers.h"

namespace server {

	class GameHandler {

	public:
		GameHandler();
		~GameHandler();

		void Start();
		void HandleLobby(const std::string& action, std::string lobbyId);
		void AddUserToLobby(const std::string& username);
		void FetchPlayerMessage(std::string playerMessage);
		void SetDifficuly(int difficulty);
		void StartGame();
		void SetWordToBeGuessed(std::string wordToBeGuessed);
		std::string GetWordToBeGuessed();
	private:
		Game m_game;
		Lobby* m_currentLobby;
		std::vector<Lobby*> m_lobbys;
		std::vector<std::string> m_currentPlayers;
		uint8_t m_numberOfTurns;
		std::string m_wordToBeGuessed;
		std::string m_playerMessage;
		WordDatabaseHandle m_wordStorage;
		UserDatabaseHandle m_userStorage;
		Timer m_timerTurn;
		Timer m_timerServer;

	};

}


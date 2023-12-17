#pragma once
#include <crow.h>
#include "DatabaseHandlers.h"
#include "gameHandlerOld.h"
#include "GameHandlers.h"
namespace server
{
	class Routing
	{
	public:
		void Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage);		//Creates all the paths and stuff
		std::string GetLastUsername() const;
		bool GetGameStart() const;
		void UpdatePlayerList(const std::vector<std::string>& playerList);
		uint8_t GetDifficulty() const;
		void SetLobbyId(const std::string& lobbyId);
	private:
		crow::SimpleApp m_app;
		std::string m_lastUsername;
		bool m_gameStart = false;
		uint8_t m_difficulty = 0;
		std::string m_lobbyId;
		std::vector<std::string> m_playerList;

	};
}
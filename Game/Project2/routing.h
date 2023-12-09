#pragma once
#include <crow.h>
#include "DatabaseHandlers.h"

namespace http
{
	class Routing
	{
	public:
		void Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage);		//Creates all the paths and stuff
		std::string GetLastUsername() const;
		bool GetGameStart() const;
		uint8_t GetDifficulty() const;

	private:
		crow::SimpleApp m_app;
		std::string m_lastUsername;
		bool m_gameStart = false;
		uint8_t m_difficulty = 0;
	};
}
#pragma once
#include <crow.h>
#include "DatabaseHandlers.h"
#include "GameHandlers.h"
namespace server
{
	class Routing
	{
	public:

		void Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage);		//Creates all the paths and stuff

	private:
		crow::SimpleApp m_app;
		GameHandlers m_gameHandlers;

	};
}
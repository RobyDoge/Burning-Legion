import game;
import lobby;

#include "timer.h"
#include "DatabaseHandlers.h"
#include "Routing.h"

namespace server {

	class GameHandler {

	public:
		GameHandler();
		~GameHandler();

		void Start();

	private:
		Game m_game;
		Lobby m_lobby;
		http::Routing m_routing;
		uint8_t m_numberOfTurns;
		WordDatabaseHandle m_wordStorage;
		UserDatabaseHandle m_userStorage;
		Timer m_timerTurn;
		Timer m_timerServer;

	};

}


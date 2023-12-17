#pragma once
import game;
import lobby;

#include <memory>
#include <string>


using game_logic::Game;
using game_logic::Lobby;

namespace server
{
	class GameHandlers
	{
	public:
		GameHandlers() = default;
		~GameHandlers();

		void CreateLobby();
		void AddUserToLobby(const std::string& username);
		void RemoveUserFromLobby(const std::string& username);

		void SetDifficulty(int difficulty);
		void SetLanguage(int language);

		void StartGame();


	private:
		std::unique_ptr<Lobby> m_lobby{};
		std::unique_ptr<Game> m_game{};
	};
};


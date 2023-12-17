#pragma once
import game;
import lobby;

#include <memory>
#include <string>
#include <queue>


using namespace game_logic;

namespace server
{
	class GameHandlers
	{
	public:
		GameHandlers() = default;
		~GameHandlers() = default;

		void CreateLobby();
		void AddUserToLobby(const std::string& username) const;
		void RemoveUserFromLobby(const std::string& username) const;

		void SetDifficulty(int difficulty) const;
		void SetLanguage(int language) const;

		void StartGame();


	private:
		std::queue<std::string> CreateWordsNeeded(const uint8_t wordsNeeded, const uint8_t difficulty, const uint8_t language) const;

	private:
		std::unique_ptr<Lobby> m_lobby{};
		std::unique_ptr<Game> m_game{};
	};
};


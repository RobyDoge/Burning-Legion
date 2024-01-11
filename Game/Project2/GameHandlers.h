#pragma once
import game;
import lobby;
import turn;


#include <memory>
#include <string>
#include <queue>
#include "Timer.h"


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
		std::vector<std::string> GetUsersNames() const;
		void SetDifficulty(int difficulty) const;
		void SetLanguage(int language) const;
		
		uint8_t GetLanguage() const;
		uint8_t GetDifficulty() const;
		std::string GetWordToBeGuessed();
		std::string CheckMessage(const std::string & message) const;
		bool GetGameStatus() const;
		bool GetTurnStatus() const;
		void StartGame();
		void TurnThreadStart( uint8_t roundIndex);
		std::string GetDrawerName() const;
		uint8_t GetDrawerPosition() const;
		void StartNextTurn( uint8_t roundIndex);
		bool IsGameStarted() const;
	private:
		std::queue<std::string> CreateWordsNeeded(const uint8_t wordsNeeded, const uint8_t difficulty, const uint8_t language) const;

	private:
		std::unique_ptr<Lobby> m_lobby{};
		std::unique_ptr<Game> m_game{};
		std::shared_ptr<Turn> m_currentTurn{};
		std::string m_wordToBeGuessed{};
		uint8_t m_drawerPosition;
		Timer m_timer{};
		bool m_gameStarted{ false };
	};
};


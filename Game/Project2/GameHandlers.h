#pragma once
import game;
import lobby;
import turn;

#include <memory>
#include <string>
#include <queue>
#include <unordered_map>

#include "Timer.h"


using namespace game_logic;

namespace server
{
	class GameHandlers
	{
	public:
		GameHandlers() = default;
		~GameHandlers() = default;

		long CreateLobby(const bool createLobby);
		void AddUserToLobby(const std::string& username) const;
		void DeleteLobby();
		void RemoveUserFromLobby(const std::string& username);
		std::vector<std::string> GetUsersNames() const;
		void SetDifficulty(int difficulty) const;
		void SetLanguage(int language) const;

		uint8_t GetLanguage() const;
		uint8_t GetDifficulty() const;
		std::string GetWordToBeGuessed();
		std::string CheckMessage(const std::string& message, const std::string& guesser) const;
		bool GetGameStatus() const;
		bool GetTurnStatus() const;
		void StartGame();
		void TurnThreadStart(uint8_t roundIndex);
		std::string GetDrawerName() const;
		uint8_t GetDrawerPosition() const;
		void AddDrawingsToDatabase();
		void StartNextTurn(uint8_t roundIndex);
		bool IsGameStarted() const;
		int GetTime() const;
		void SetCurrentGuess(const std::string& guess);
		std::string GetCurrentGuess() const;
		std::string GetDrawing() const;
		void SetDrawing(const std::string& drawing);
		std::vector<std::pair<std::string, int16_t>> GetPlayersTurnPoints() const;
		std::vector<std::pair<std::string, int16_t>> GetPlayersGamePoints() const;
		std::vector<std::pair<std::string, int16_t>> GetSortedPlayers() const;

	private:
		static std::queue<std::string> CreateWordsNeeded(const uint8_t wordsNeeded, const uint8_t difficulty, const uint8_t language);

	private:
		std::unique_ptr<Lobby> m_lobby{};
		std::unique_ptr<Game> m_game{};
		std::shared_ptr<Turn> m_currentTurn{};
		std::string m_wordToBeGuessed{};
		uint8_t m_drawerPosition;
		Timer m_timer{};
		bool m_gameStarted{ false };
		mutable int m_correctGuesses = 0;
		int m_currentTime{};
		std::string m_currentGuess{};
		std::string m_drawing{};
		std::string m_currentGuesser{};
		std::vector<std::pair<std::string, int16_t>> m_currentTurnPoints{};
		std::unordered_map<std::string, std::vector<std::string>> m_currentMatchDrawings{};
		std::vector<std::pair<std::string, int16_t>> m_winners{};
	};

}

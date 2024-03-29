#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"
#include <vector>
#include <atomic>
#include <thread>

class LobbyWindow : public QMainWindow
{
	Q_OBJECT
public:
	LobbyWindow(const std::string& username, QWidget* parent = nullptr);
	~LobbyWindow() override;

private:
	void StartUpdatingThread();
	void StopUpdatingThread();
	void UpdatePlayersListWidget(QListWidget* listWidget) const;
	void PlayerJoinedLobby();
	void PlayerChangedDifficulty();
	void PlayerChangedLanguage();
	void GameStartThread();
	void GameStarted();

private slots:
	void StartGameButton_Clicked() const;
	void Difficulty_Changed();
	void Language_Changed();

private:
	std::thread m_updateThread;
	QTimer* m_gameStatusTimer;
	Ui::lobbyClass ui;
	std::vector<std::string> m_players{};
	std::string m_username{};
	uint8_t m_difficulty{ 0 };
	uint8_t m_language{ 0 };

	std::atomic<bool> m_stopThread;
	bool m_isLeader{ false };
	bool m_gameStart{ false };

private:
	inline static const std::unordered_map<std::string, uint8_t> DIFFICULTY_MAP
	{
		{"No Difficulty", 0},
		{"Easy", 1},
		{"Normal", 2},
		{"Hard", 3}
	};

	inline static const std::unordered_map<std::string, uint8_t> LANGUAGE_MAP
	{
		{"English", 0},
		{"Romanian", 1},
		{"Spanish", 2}
	};
};

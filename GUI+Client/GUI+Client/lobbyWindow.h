#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"
#include <vector>
#include "Client.h"


class LobbyWindow : public QMainWindow
{
		Q_OBJECT
public:
	LobbyWindow(const std::string& username,QWidget *parent = nullptr);
	~LobbyWindow() override;

private:
	void StartUpdatingThread();
	void StopUpdatingThread();
	void UpdatePlayersListWidget(QListWidget* listWidget);
	void PlayerJoinedLobby();
	uint8_t ConvertDifficultyToInt(const std::string& difficulty);
	uint8_t ConvertLanguageToInt(const std::string& language);
	void PlayerChangedDifficulty();
	void PlayerChangedLanguage();

private slots:
	void StartGameButton_Clicked();
	void Difficulty_Changed();
	void Language_Changed();

private:
	Ui::lobbyClass ui;
	std::vector<std::string> m_players{};
	std::string m_username{};
	uint8_t m_difficulty{0};
	uint8_t m_language{0};
	Client m_client{};
	std::atomic<bool> m_stopThread{};
};

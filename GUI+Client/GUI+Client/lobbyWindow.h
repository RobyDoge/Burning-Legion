#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"
#include <vector>
#include "Client.h"


class LobbyWindow : public QMainWindow
{
public:
	LobbyWindow(std::string username,QWidget *parent = nullptr);
	~LobbyWindow();

private:

	void startUpdatingThread();
	void stopUpdatingThread();
	void UpdatePlayersListWidget(QListWidget* listWidget);
	void PlayerJoinedLobby();
	uint8_t ConvertDifToInt(const std::string& difficulty);
	uint8_t ConvertLangToInt(const std::string& language);
	void PlayerChangedDifficulty();
	void PlayerChangedLanguage();

private slots:

	void startGameButton_clicked();
	void difficultyBoxIndexChanged();
	void languageBoxIndexChanged();
private:
	Ui::lobbyClass ui;
	std::vector<std::string> m_players;
	std::string m_username;
	uint8_t m_difficulty;
	uint8_t m_language;
	Client m_client;
	std::atomic<bool> stopThread;
};

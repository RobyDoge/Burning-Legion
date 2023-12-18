#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"
#include <vector>
#include "gameWindow.h"
#include "client.h"
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
	uint8_t ConvertToInt(const std::string& difficulty);

private slots:

	void startGameButton_clicked();
	void difficultyBoxIndexChanged();
private:
	Ui::lobbyClass ui;
	std::vector<std::string> m_players;
	std::string m_username;
	QString m_difficulty;
	Client m_client;
	std::atomic<bool> stopThread;
};

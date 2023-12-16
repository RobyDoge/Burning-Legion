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

private slots:
	void startGameButton_clicked();
private:
	Ui::lobbyClass ui;
	std::vector<std::string> m_players;
	std::string m_username;
	QString m_difficulty;
	void UpdatePlayersListWidget(QListWidget* listWidget);
	void PlayerJoinedLobby();
	Client m_client;
};

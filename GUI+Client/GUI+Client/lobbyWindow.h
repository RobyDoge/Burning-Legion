#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"
#include <vector>
class LobbyWindow : public QMainWindow
{
public:
	LobbyWindow(QWidget *parent = nullptr);
	~LobbyWindow();

private slots:
	void startGameButton_clicked();
private:
	Ui::lobbyClass ui;
	std::vector<std::string> m_players;
	QString m_difficulty;
	void UpdatePlayersListWidget(QListWidget* listWidget);
	void PlayerJoinedLobby();
};

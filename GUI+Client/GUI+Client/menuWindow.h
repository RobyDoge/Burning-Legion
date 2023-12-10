#pragma once

#include <QMainWindow>
#include <QString>
#include "ui_menuWindow.h"
#include "lobbyWindow.h"
#include "client.h"
#include <list>

class MenuWindow : public QMainWindow
{

public:
	MenuWindow(std::string username , QWidget *parent = nullptr);
	~MenuWindow();
	void openLobbyWindow();

private:
	void GetBestScoreAndLastMatches();
private slots:
	void createLobbyButton_clicked();
	void joinLobbyButton_clicked();

private:
	Ui::MenuWindowClass ui;
	QString m_code;
	std::string m_username;
	uint16_t m_bestScore;
	std::list<int16_t> m_lastMatchesPoints;
	Client m_client;
};

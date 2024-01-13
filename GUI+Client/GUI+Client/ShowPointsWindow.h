#pragma once

#include <QMainWindow>
#include "ui_showPointsWindow.h"
#include "client.h"
#include <algorithm>

class ShowPointsWindow : public QMainWindow
{
	

public:
	ShowPointsWindow(QWidget *parent = nullptr);
	~ShowPointsWindow();
private slots:

private:
	Ui::ShowPointsWindowClass ui;
	void SortPlayers();
	void DisplayPlayers();
	std::vector<std::pair<std::string,int >> m_players;
	std::vector<int> m_playersPoints;
	std::vector<std::string> m_playersNames;
	Client m_client;
};




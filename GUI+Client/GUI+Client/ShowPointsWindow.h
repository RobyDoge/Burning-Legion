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
	void nextButton_clicked();

private:
	Ui::ShowPointsWindowClass ui;
	void SortPlayers();
	void DisplayPlayers();
	std::vector<std::pair<std::string, uint16_t>> m_players;
	Client m_client;
};




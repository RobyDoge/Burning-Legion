#pragma once
#include <QMainWindow>
#include "ui_showPointsWindow.h"

class ShowPointsWindow : public QMainWindow
{
	

public:
	ShowPointsWindow(QWidget *parent = nullptr);
	~ShowPointsWindow() override = default;


private:
void SortPlayers();
void DisplayPlayers();

private:
	Ui::ShowPointsWindowClass ui;
	std::vector<std::pair<std::string,int >> m_players;
};




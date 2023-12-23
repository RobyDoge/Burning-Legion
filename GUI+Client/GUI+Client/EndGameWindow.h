#pragma once

#include <QMainWindow>
#include "ui_endGameWindow.h"

class EndGameWindow : public QMainWindow
{


public:
	EndGameWindow(QWidget *parent = nullptr);
	~EndGameWindow();

private:
	Ui::EndGameWindowClass ui;
	void CalculateWinner() const;
	void DisplayPlayers() const;
	std::vector<std::pair<std::string,uint16_t>> m_players;
	std::string m_winner;
};



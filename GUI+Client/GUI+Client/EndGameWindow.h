#pragma once

#include <QMainWindow>
#include "ui_endGameWindow.h"

//this class should be adjusted after the request for the list of players is implemented
class EndGameWindow : public QMainWindow
{
public:
	EndGameWindow(QWidget *parent = nullptr);
	~EndGameWindow() override = default;

private slots:
	void BackButton_Clicked();
	//this function is implemented on the server and should ask for the list of players ordered by their score
	void CalculateWinner() const;
	void DisplayPlayers() const;

private:
	Ui::EndGameWindowClass ui;
	std::vector<std::pair<std::string,uint16_t>> m_players{};
	std::string m_winner{};
};



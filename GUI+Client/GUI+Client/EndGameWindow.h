#pragma once

#include <QMainWindow>
#include "ui_endGameWindow.h"
#include "client.h"

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
	std::vector<std::pair<std::string, int >> m_players;
	std::vector<int> m_playersPoints;
	std::vector<std::string> m_playersNames;
	Client m_client;
	std::string m_winner{};
};



#pragma once
#include <string>
#include <QMainWindow>
#include "ui_endGameWindow.h"
#include "client.h"


class EndGameWindow : public QMainWindow
{
public:
	EndGameWindow(QWidget *parent = nullptr);
	~EndGameWindow() override = default;

private slots:
	void BackButton_Clicked();

private:
	void DisplayPlayers() const;

private:
	Ui::EndGameWindowClass ui;
	std::vector<std::pair<std::string, int16_t >> m_players;
};



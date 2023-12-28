#pragma once

#include "ui_endRoundWindow.h"
#include <QMainWindow>

class EndRoundWindow : public QMainWindow
{
	Q_OBJECT

public:
	EndRoundWindow(QWidget *parent = nullptr);
	~EndRoundWindow();

private slots:
	void nextButton_clicked();
private:
	Ui::EndRoundWindowClass ui;
	void SortPlayers() const;
	void DisplayPlayers() const;
	std::vector<std::pair<std::string, uint16_t>> m_players;
	Client m_client;
};

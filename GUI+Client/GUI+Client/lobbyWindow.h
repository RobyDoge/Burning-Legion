#pragma once

#include <QMainWindow>
#include "ui_lobbyWindow.h"

class LobbyWindow : public QMainWindow
{

public:
	LobbyWindow(QWidget *parent = nullptr);
	~LobbyWindow();

private:
	Ui::lobbyClass ui;
};

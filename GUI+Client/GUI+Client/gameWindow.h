#pragma once

#include <QMainWindow>
#include "ui_gameWindow.h"

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = nullptr);
	~GameWindow();

private:
	Ui::gameWindowClass ui;
};

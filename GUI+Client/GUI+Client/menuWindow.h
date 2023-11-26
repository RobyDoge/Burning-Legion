#pragma once

#include <QMainWindow>
#include <QString>
#include "ui_menuWindow.h"

class MenuWindow : public QMainWindow
{

public:
	MenuWindow(QWidget *parent = nullptr);
	~MenuWindow();
	void openLobbywindow();
	void on_createLobbyButton_clicked();
	void on_joinLobbyButton_clicked();

private:
	Ui::MenuWindowClass ui;
	QString m_code;
};

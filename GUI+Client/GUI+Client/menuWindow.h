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

private slots:
	void createLobbyButton_clicked();
	void joinLobbyButton_clicked();

private:
	Ui::MenuWindowClass ui;
	QString m_code;
};

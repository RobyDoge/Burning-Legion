#pragma once

#include <QMainWindow>
#include "ui_loginWindow.h"

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
    void openGameWindow();
	void on_loginButton_clicked();
	void on_signinButton_clicked();

private:
	Ui::loginClass ui;
	QString m_username;
	QString m_password;
};

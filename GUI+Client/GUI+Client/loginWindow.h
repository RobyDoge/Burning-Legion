#pragma once

#include <QMainWindow>
#include <QString>
#include "ui_loginWindow.h"
//#include "client.h"
class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
    void openMenuWindow();
	void on_loginButton_clicked();
	void on_signinButton_clicked();

private:
	Ui::loginClass ui;
	QString m_username;
	QString m_password;
	//Client m_loginClient;
};

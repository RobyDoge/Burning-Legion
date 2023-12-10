#pragma once

#include <QMainWindow>
#include <QString>
#include <string>
#include "ui_loginWindow.h"
#include "client.h"
class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();
	void openMenuWindow(std::string username);
	std::string GetUsername();

private slots:
	void loginButton_clicked();
	void signinButton_clicked();

private:
	Ui::loginClass ui;
	std::string m_username;
	std::string m_password;
	Client m_loginClient;
};

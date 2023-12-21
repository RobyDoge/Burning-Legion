#pragma once
#include <QMainWindow>
#include <QString>
#include <string>
#include "ui_loginWindow.h"
#include "Client.h"

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow() override = default;
	void OpenMenuWindow(const std::string& username);
	std::string GetUsername();

private slots:
	void LoginButton_Clicked();
	void SigninButton_Clicked();

private:
	Ui::loginClass ui;
	std::string m_username{};
	std::string m_password{};
	Client m_loginClient{};
};

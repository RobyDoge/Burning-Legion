#pragma once
#include <QMainWindow>
#include <QString>
#include <string>
#include "ui_loginWindow.h"

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = nullptr);
	~LoginWindow() override = default;


private:
	void OpenMenuWindow();
	std::string GetUsername() const;

private slots:
	void LoginButton_Clicked();
	void SigninButton_Clicked();

private:
	Ui::loginClass ui;
	std::string m_username{};
	std::string m_password{};
};

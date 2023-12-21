#pragma once

#include <QMainWindow>
#include "ui_signupWindow.h"
#include "Client.h"

class SignUpWindow : public QMainWindow
{
	Q_OBJECT

public:
	SignUpWindow(QWidget *parent = nullptr);
	~SignUpWindow() override = default;

private slots:
	void SignUpButton_Clicked();
	void LoginButton_Clicked();
	void Username_LineEditingFinished();

private:
	void CreateLoginWindow();


private:
	Ui::signupWindowClass ui;
	QString m_username{};
	QString m_password{};
	QString m_confirmPassword{};
	Client m_signUpClient{};

};

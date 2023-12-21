#pragma once

#include <QMainWindow>
#include "ui_signupWindow.h"
#include "Client.h"

class SignupWindow : public QMainWindow
{
	Q_OBJECT

public:
	SignupWindow(QWidget *parent = nullptr);
	~SignupWindow();

private slots:
	void signupButton_clicked();
	void signupLogginButton_clicked();
	void onUsernameEditingFinished();
 
private:
	Ui::signupWindowClass ui;
	QString m_username;
	QString m_password;
	QString m_confirmPassword;
	Client m_signupClient;

};

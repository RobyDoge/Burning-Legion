#include "LoginWindow.h"
#include "SignUpWindow.h"
#include "MenuWindow.h"
#include <QString>

LoginWindow::LoginWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.loginPassword->setEchoMode(QLineEdit::Password);
	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::LoginButton_Clicked);
    connect(ui.signinButton, &QPushButton::clicked, this, &LoginWindow::SigninButton_Clicked);

}
void LoginWindow::LoginButton_Clicked()
{
    m_username = ui.loginUsername->text().toUtf8().constData();
    m_password = ui.loginPassword->text().toUtf8().constData();

	if (m_username.empty() || m_password.empty())
	{
        ui.messageLabel->setText("Please enter both username and password.");
        return;
    }

    //Sends username and password to the server to check with the database  
    if (const long response = m_loginClient.GetLoginResponse(m_username, m_password); 
        response == 200 || response == 201)
    {
	    OpenMenuWindow(m_username);
    }
    else
    {
	    ui.messageLabel->setText("Username or Password incorrect");
    }
}

void LoginWindow::SigninButton_Clicked() 
{
	auto* signUpWindow = new SignUpWindow();
    signUpWindow->show();
    this->destroy();
}
void LoginWindow::OpenMenuWindow(const std::string& username)
{
	auto* menuWindow = new MenuWindow(username); 
    menuWindow->show();
    this->deleteLater();
}

std::string LoginWindow::GetUsername()
{
	return m_username;
}

#include "loginWindow.h"
#include "gameWindow.h"
#include "signupWindow.h"
#include "menuWindow.h"
#include <QString>


LoginWindow::LoginWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.loginPassword->setEchoMode(QLineEdit::Password);
	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::loginButton_clicked);
    connect(ui.signinButton, &QPushButton::clicked, this, &LoginWindow::signinButton_clicked);

}

LoginWindow::~LoginWindow()
{
    this->destroy();
}

void LoginWindow::loginButton_clicked()
{
    m_username = ui.loginUsername->text().toUtf8().constData();
    m_password = ui.loginPassword->text().toUtf8().constData();

	if (m_username.empty() || m_password.empty())
	{
        ui.messageLabel->setText("Please enter both username and password.");
        return;
    }

    long response = m_loginClient.GetLoginResponse(m_username, m_password); 
    //Sends username and password to the server to check with the database  
    if (response == 200 || response == 201)
        openMenuWindow(m_username);
    else
        ui.messageLabel->setText("Username or Password incorrect");
    openMenuWindow(m_username);
}

void LoginWindow::signinButton_clicked() 
{
    SignupWindow* signupWindow = new SignupWindow();
    signupWindow->show();
    this->destroy();
}
void LoginWindow::openMenuWindow(std::string username)
{
    MenuWindow* menuWindow = new MenuWindow(username,this); 
    menuWindow->show();
    this->destroy();
}

std::string LoginWindow::GetUsername()
{
	return m_username;
}

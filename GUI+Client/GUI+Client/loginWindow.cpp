#include "LoginWindow.h"
#include "SignUpWindow.h"
#include "MenuWindow.h"
#include "Client.h"
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
    if (const long response = Client::Return_LoginResponse(m_username, m_password); 
        response == 200 || response == 201)
    {
	    OpenMenuWindow();
        return;
    }
	ui.messageLabel->setText("Username or Password incorrect");
}

void LoginWindow::SigninButton_Clicked() 
{
	auto* signUpWindow = new SignUpWindow();
    signUpWindow->show();
    this->destroy();
}

void LoginWindow::OpenMenuWindow()
{
	auto* menuWindow = new MenuWindow(std::move(m_username)); 
    menuWindow->show();
    this->destroy();
}

std::string LoginWindow::GetUsername() const
{
	return m_username;
}

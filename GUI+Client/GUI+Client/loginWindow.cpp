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
    m_username = ui.loginUsername->text();
    m_password = ui.loginPassword->text();

    if (m_username.isEmpty() || m_password.isEmpty()) {
        ui.messageLabel->setText("Please enter both username and password.");
        return;
    }

    long response = m_loginClient.GetLoginResponse(m_username.toUtf8().constData(), m_password.toUtf8().constData()); 
    //Sends username and password to the server to check with the database  
    if (response == 200 || response == 201)
        openMenuWindow();
    else
        ui.messageLabel->setText("Username or Password incorrect");
    openMenuWindow();
}

void LoginWindow::signinButton_clicked() 
{
    SignupWindow* signupWindow = new SignupWindow();
    signupWindow->show();
    this->destroy();
}
void LoginWindow::openMenuWindow()
{
    MenuWindow* menuWindow = new MenuWindow(this); 
    menuWindow->show();
    this->destroy();
}

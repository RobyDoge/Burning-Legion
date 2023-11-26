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
	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
    connect(ui.signinButton, &QPushButton::clicked, this, &LoginWindow::on_signinButton_clicked);

}

LoginWindow::~LoginWindow()
{}

void LoginWindow::on_loginButton_clicked()
{
    m_username = ui.loginUsername->text();
    m_password = ui.loginPassword->text();

    if (m_username.isEmpty() || m_password.isEmpty()) {
        ui.messageLabel->setText("Please enter both username and password.");
        return;
    }

    //m_loginClient.GetLoginResponse(m_username.toStdString(),m_password.toStdString());
    openMenuWindow();
    
    // Altfel:
    ui.messageLabel->setText("Username or Password incorrect");
}
void LoginWindow::on_signinButton_clicked() 
{
    SignupWindow* signupWindow = new SignupWindow(this);
    signupWindow->show();
    this->destroy();
}
void LoginWindow::openMenuWindow()
{
    MenuWindow* menuWindow = new MenuWindow(this); 
    menuWindow->show();
    this->destroy();
}

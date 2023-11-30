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
{
    this->destroy();
}

void LoginWindow::on_loginButton_clicked()
{
    m_username = ui.loginUsername->text();
    m_password = ui.loginPassword->text();

    if (m_username.isEmpty() || m_password.isEmpty()) {
        ui.messageLabel->setText("Please enter both username and password.");
        return;
    }
    // Using dummy username and password for now because .toStdString DOESNT WORK
        std::string username = "gigel";
        std::string password = "parola";
    long response = m_loginClient.GetLoginResponse(username, password);
    if (response == 200 || response == 201)
        openMenuWindow();
    else
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

#include "loginWindow.h"
#include "gameWindow.h"
#include "signupWindow.h"

LoginWindow::LoginWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.loginUsername->setPlaceholderText("Username");
    ui.loginPassword->setPlaceholderText("Password");
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

    // Verificați în baza de date dacă acest utilizator există
    // Dacă da:
    openGameWindow();
    
    // Altfel:
    ui.messageLabel->setText("Username or Password incorrect");
}
void LoginWindow::on_signinButton_clicked() 
{
    SignupWindow* signupWindow = new SignupWindow(this);
    signupWindow->show();
    this->destroy();
}
void LoginWindow::openGameWindow()
{
    GameWindow* gameWindow = new GameWindow(this); 
    gameWindow->show();
    this->destroy();
}

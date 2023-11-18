#include "loginWindow.h"
#include "gameWindow.h"
LoginWindow::LoginWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    //ui.loginUsername->setPlaceholderText("Enter Username");
    //ui.loginPassword->setPlaceholderText("Enter Password");

	connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);
    connect(ui.signinButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);

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
void LoginWindow::openGameWindow()
{
    GameWindow* gameWindow = new GameWindow(this); 
    gameWindow->show();
    this->destroy();
}

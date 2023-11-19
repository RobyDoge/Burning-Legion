#include "signupWindow.h"
#include "loginWindow.h"
SignupWindow::SignupWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.signupUsernameLine->setPlaceholderText("Username");
	ui.sigupPasswordLine->setPlaceholderText("Create Password");
	ui.sigupPasswordRepeatLine->setPlaceholderText("Confirm Password");

	connect(ui.signupButton, &QPushButton::clicked, this, &SignupWindow::on_signupButton_clicked);
	connect(ui.signupLogginButton, &QPushButton::clicked, this, &SignupWindow::on_signupLogginButton_clicked);
}

SignupWindow::~SignupWindow()
{}



void SignupWindow::on_signupButton_clicked() 
{	
	QString dummy_username;
	m_username = ui.signupUsernameLine->text();
	m_password = ui.sigupPasswordLine->text();
	m_confirmPassword = ui.sigupPasswordRepeatLine->text();
	if (m_password!= m_confirmPassword)
	{
		ui.errorLabel->setText("Please check that both passwords are correct!");
		return;
	}
	//verifica daca usernameul exista deja in baza de date
	if (m_username == dummy_username) 
	{
		ui.errorLabel->setText("Username already exists!");
		return;
	}
	//Adauga userul si parola in baza de date
	on_signupLogginButton_clicked();
	
}


void SignupWindow::on_signupLogginButton_clicked() 
{
	LoginWindow* loginWindow = new LoginWindow(this);
	loginWindow->show();
	this->destroy();
}

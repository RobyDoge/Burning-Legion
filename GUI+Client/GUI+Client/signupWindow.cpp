#include "SignUpWindow.h"
#include "LoginWindow.h"
#include "Client.h"

SignUpWindow::SignUpWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.sigupPasswordLine->setEchoMode(QLineEdit::Password);
	ui.sigupPasswordRepeatLine->setEchoMode(QLineEdit::Password);


	connect(ui.signupButton, &QPushButton::clicked, this, &SignUpWindow::SignUpButton_Clicked);
	connect(ui.signupLogginButton, &QPushButton::clicked, this, &SignUpWindow::LoginButton_Clicked);
}

bool SignUpWindow::Username_LineEditingFinished() 
{
	m_username = ui.signupUsernameLine->text();
	QString data = QCoreApplication::applicationDirPath();
	if (const long response = Client::Return_UsernameAvailability(m_username.toUtf8().constData()); 
		response == 200 || response == 201)
	{
		return true;
	}
	return false;
}

void SignUpWindow::SignUpButton_Clicked() 
{	
	m_password = ui.sigupPasswordLine->text();
	m_confirmPassword = ui.sigupPasswordRepeatLine->text();
	if (m_password!= m_confirmPassword)
	{
		ui.errorLabel->setText("Please check that both passwords are correct!");
		return;
	}

	if (!Username_LineEditingFinished())
	{
		ui.errorLabel->setText("Username is not available!");
		return;
	}
	if (const long response = Client::Return_CreateUserInDatabase(m_username.toUtf8().constData(),
	                                                              m_password.toUtf8().constData());
		response == 200 || response == 201)
	{
		LoginButton_Clicked();
		return;
	}
	ui.errorLabel->setText("Error while creating account!");
}

void SignUpWindow::LoginButton_Clicked()
{
	auto* loginWindow = new LoginWindow();
	loginWindow->show();
	this->destroy();

}

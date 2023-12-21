#include "SignUpWindow.h"
#include "LoginWindow.h"

SignUpWindow::SignUpWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.sigupPasswordLine->setEchoMode(QLineEdit::Password);
	ui.sigupPasswordRepeatLine->setEchoMode(QLineEdit::Password);


	connect(ui.signupButton, &QPushButton::clicked, this, &SignUpWindow::SignUpButton_Clicked);
	connect(ui.signupLogginButton, &QPushButton::clicked, this, &SignUpWindow::LoginButton_Clicked);
	connect(ui.signupUsernameLine, &QLineEdit::editingFinished, this, &SignUpWindow::Username_LineEditingFinished);

}

void SignUpWindow::Username_LineEditingFinished() 
{
	m_username = ui.signupUsernameLine->text();
	QString data = QCoreApplication::applicationDirPath();
	if (const long response = m_signUpClient.ConfirmUsernameAvailable(m_username.toUtf8().constData()); 
		response == 200 || response == 201)
	{
		const QPixmap available(QCoreApplication::applicationDirPath() + "/Checked.png");			//This should be moved to .h (i think) 
		ui.signupUsernameCheckLabel->setPixmap(available);								//The label becomes the image ( initally invisible)
		ui.signupUsernameCheckLabel->setFixedSize(available.size());
	}
	else
	{
		const QPixmap notAvailable(QCoreApplication::applicationDirPath() + "/!Checked.png");      //Sets a pixmap to an image(for the available or not at username)
		ui.signupUsernameCheckLabel->setPixmap(notAvailable);
		ui.signupUsernameCheckLabel->setFixedSize(notAvailable.size());

	}

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

	const QPixmap notAvailable(QCoreApplication::applicationDirPath() + "/!Checked.png");      //Sets a pixmap to an image(for the available or not at username)
	if (ui.signupUsernameCheckLabel->pixmap().toImage() == notAvailable.toImage())
	{
		ui.errorLabel->setText("Username is not available!");
		return;
	}

	if (const long response = m_signUpClient.AddUser(m_username.toUtf8().constData(), m_password.toUtf8().constData()); 
		response == 200 || response == 201)
	{
		CreateLoginWindow();
	}
	else
	{
		ui.errorLabel->setText("Error while creating account!");
	}
}

void SignUpWindow::CreateLoginWindow()
{
	auto* loginWindow = new LoginWindow();
	loginWindow->show();
	this->destroy();
}


void SignUpWindow::LoginButton_Clicked()
{
	auto* loginWindow = new LoginWindow();
	loginWindow->show();
	this->destroy();

}

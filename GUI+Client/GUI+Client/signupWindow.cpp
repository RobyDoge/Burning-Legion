#include "signupWindow.h"
#include "loginWindow.h"
SignupWindow::SignupWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.sigupPasswordLine->setEchoMode(QLineEdit::Password);
	ui.sigupPasswordRepeatLine->setEchoMode(QLineEdit::Password);


	connect(ui.signupButton, &QPushButton::clicked, this, &SignupWindow::on_signupButton_clicked);
	connect(ui.signupLogginButton, &QPushButton::clicked, this, &SignupWindow::on_signupLogginButton_clicked);
	connect(ui.signupUsernameLine, &QLineEdit::editingFinished, this, &SignupWindow::onUsernameEditingFinished);

}

SignupWindow::~SignupWindow()
{}

void SignupWindow::onUsernameEditingFinished() 
{
	m_username = ui.signupUsernameLine->text();
	QString data = QCoreApplication::applicationDirPath();
	QPixmap available(QCoreApplication::applicationDirPath() +"/Checked.png");
	QPixmap notAvailable(QCoreApplication::applicationDirPath() +"/!Checked.png");
	//long response = m_signupClient.ConfirmUsernameAvailable(m_username.toStdString());
	int response = 200;
	if (response == 201)
	{
		ui.signupUsernameCheckLabel->setPixmap(available);
		ui.signupUsernameCheckLabel->setFixedSize(available.size());
	}
	else
	{
		ui.signupUsernameCheckLabel->setPixmap(notAvailable);
		ui.signupUsernameCheckLabel->setFixedSize(notAvailable.size());

	}

}

void SignupWindow::on_signupButton_clicked() 
{	
	QString dummy_username;
	m_password = ui.sigupPasswordLine->text();
	m_confirmPassword = ui.sigupPasswordRepeatLine->text();
	if (m_password!= m_confirmPassword)
	{
		ui.errorLabel->setText("Please check that both passwords are correct!");
		return;
	}

	////long response = m_signupClient.ConfirmUsernameAvailable(m_username.toStdString());

	//if (response == 200)
	//{
	//	on_signupLogginButton_clicked();
	//}
	//else 
	//{
	//	ui.errorLabel->setText("Username already exists!");
	//	return;
	//}
		
}


void SignupWindow::on_signupLogginButton_clicked() 
{
	LoginWindow* loginWindow = new LoginWindow(this);
	loginWindow->show();
	this->destroy();
}

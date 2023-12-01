#include "signupWindow.h"
#include "loginWindow.h"
SignupWindow::SignupWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.sigupPasswordLine->setEchoMode(QLineEdit::Password);
	ui.sigupPasswordRepeatLine->setEchoMode(QLineEdit::Password);


	connect(ui.signupButton, &QPushButton::clicked, this, &SignupWindow::signupButton_clicked);
	connect(ui.signupLogginButton, &QPushButton::clicked, this, &SignupWindow::signupLogginButton_clicked);
	connect(ui.signupUsernameLine, &QLineEdit::editingFinished, this, &SignupWindow::onUsernameEditingFinished);

}

SignupWindow::~SignupWindow()
{
	this->destroy();
}

void SignupWindow::onUsernameEditingFinished() 
{
	m_username = ui.signupUsernameLine->text();
	QString data = QCoreApplication::applicationDirPath();
	QPixmap available(QCoreApplication::applicationDirPath() +"/Checked.png");			//This should be moved to .h (i think) 
	QPixmap notAvailable(QCoreApplication::applicationDirPath() +"/!Checked.png");      //Sets a pixmap to an image(for the available or not at username)

	long response = m_signupClient.ConfirmUsernameAvailable(m_username.toUtf8().constData());
	if (response == 200 || response == 201)
	{
		ui.signupUsernameCheckLabel->setPixmap(available);								//The label becomes the image ( initally invisible)
		ui.signupUsernameCheckLabel->setFixedSize(available.size());
	}
	else
	{
		ui.signupUsernameCheckLabel->setPixmap(notAvailable);
		ui.signupUsernameCheckLabel->setFixedSize(notAvailable.size());

	}

}

void SignupWindow::signupButton_clicked() 
{	
	m_password = ui.sigupPasswordLine->text();
	m_confirmPassword = ui.sigupPasswordRepeatLine->text();
	if (m_password!= m_confirmPassword)
	{
		ui.errorLabel->setText("Please check that both passwords are correct!");
		return;
	}


	long response = m_signupClient.AddUser(m_username.toUtf8().constData(), m_password.toUtf8().constData());

	if (response == 200 || response == 201)
	{
		signupLogginButton_clicked();
	}
	else 
	{
		ui.errorLabel->setText("Error while creating account!");
		return;
	}
		
}


void SignupWindow::signupLogginButton_clicked()
{
	LoginWindow* loginWindoww = new LoginWindow(this);
	loginWindoww->show();
	this->destroy();

}

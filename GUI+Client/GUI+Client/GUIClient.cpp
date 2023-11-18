#include "GUIClient.h"

GUIClient::GUIClient(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.loginUsername->setPlaceholderText("UserName");
    ui.loginPassword->setPlaceholderText("Password");
    ui.signupButton->setStyleSheet("QPushButton{background:transparent;}");
}

GUIClient::~GUIClient()
{}

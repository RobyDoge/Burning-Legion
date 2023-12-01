#include "menuWindow.h"
MenuWindow::MenuWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.createLobbyButton, &QPushButton::clicked, this, &MenuWindow::createLobbyButton_clicked);
    connect(ui.joinLobbyButton, &QPushButton::clicked, this, &MenuWindow::joinLobbyButton_clicked);

}

MenuWindow::~MenuWindow()
{
}


void MenuWindow::openLobbywindow()
{
    //to do when LobbyWindow is created
}

void MenuWindow::createLobbyButton_clicked()
{
    /*
    LobbyWindow* lobbyWindow=new LobbyWindow(this);
    lobbyWindow->show();
    this->destroy();
    */
}

void MenuWindow::joinLobbyButton_clicked()
{
    m_code = ui.joinLobbyCode->text();
    //to do when LobbyWindow is created
}

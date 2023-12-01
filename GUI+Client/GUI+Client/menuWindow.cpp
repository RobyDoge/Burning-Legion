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


void MenuWindow::openLobbyWindow()
{
    LobbyWindow* lobbyWindow = new LobbyWindow();
    lobbyWindow->show();
    this->destroy();
    
}

void MenuWindow::createLobbyButton_clicked()
{
    openLobbyWindow();
}

void MenuWindow::joinLobbyButton_clicked()
{
    m_code = ui.joinLobbyCode->text();
    openLobbyWindow();
}

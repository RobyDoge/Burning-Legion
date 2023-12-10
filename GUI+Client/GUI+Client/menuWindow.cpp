#include "menuWindow.h"
MenuWindow::MenuWindow(std::string username,QWidget* parent)
    : m_username (username) , QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.createLobbyButton, &QPushButton::clicked, this, &MenuWindow::createLobbyButton_clicked);
    connect(ui.joinLobbyButton, &QPushButton::clicked, this, &MenuWindow::joinLobbyButton_clicked);
	GetBestScoreAndLastMatches();
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

void MenuWindow::GetBestScoreAndLastMatches()
{
	std::pair<uint16_t, std::list<int16_t>> bestScoreAndLastMatchesPoints = m_client.GetBestScoreAndLastMatchesPoints(m_username);
   	m_bestScore = bestScoreAndLastMatchesPoints.first;
	m_lastMatchesPoints = bestScoreAndLastMatchesPoints.second;
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

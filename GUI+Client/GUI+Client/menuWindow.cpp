#include "MenuWindow.h"
#include "LobbyWindow.h"
#include "Client.h"

MenuWindow::MenuWindow(const std::string& username,QWidget* parent)
    : m_username (username) , QMainWindow(parent)
{
    ui.setupUi(this);
   
    connect(ui.createLobbyButton, &QPushButton::clicked, this, &MenuWindow::CreateLobbyButton_Clicked);
    connect(ui.joinLobbyButton, &QPushButton::clicked, this, &MenuWindow::JoinLobbyButton_Clicked);
	GetBestScoreAndLastMatches();
}

void MenuWindow::OpenLobbyWindow()
{
    auto* lobbyWindow = new LobbyWindow(std::move(m_username));
    lobbyWindow->show();
    this->destroy();
}

void MenuWindow::GetBestScoreAndLastMatches()
{
	const auto usernameString = QString(m_username.c_str());
    ui.usernameLabel->setText(usernameString);
    //this function needs to be updated after the saving of drawings are done
   /* std::pair<uint16_t, std::list<int16_t>> bestScoreAndLastMatchesPoints = Client::GetBestScoreAndLastMatchesPoints(m_username);
    m_bestScore = bestScoreAndLastMatchesPoints.first;
    m_lastMatchesPoints = bestScoreAndLastMatchesPoints.second;
    ui.scoreList->addItem("Best Score: " + QString::number(m_bestScore));
    for (const uint16_t& points : m_lastMatchesPoints) 
    {
        ui.scoreList->addItem(QString::number(points));
    }
    ui.scoreList->setMaximumHeight(6 * ui.scoreList->sizeHintForRow(0));*/
}

void MenuWindow::CreateLobbyButton_Clicked()
{
    Client::Send_CreateLobby_Signal();
    OpenLobbyWindow();
}

void MenuWindow::JoinLobbyButton_Clicked()
{
    OpenLobbyWindow();
}

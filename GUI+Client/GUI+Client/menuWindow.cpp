#include "MenuWindow.h"
MenuWindow::MenuWindow(std::string username,QWidget* parent)
    : m_username (username) , QMainWindow(parent)
{
    ui.setupUi(this);
    //ui.usernameLabel->setText(QString::fromStdString("Username: " + m_username));
    connect(ui.createLobbyButton, &QPushButton::clicked, this, &MenuWindow::createLobbyButton_clicked);
    connect(ui.joinLobbyButton, &QPushButton::clicked, this, &MenuWindow::joinLobbyButton_clicked);
	GetBestScoreAndLastMatches();
}

MenuWindow::~MenuWindow()
{
}


void MenuWindow::openLobbyWindow()
{
    LobbyWindow* lobbyWindow = new LobbyWindow(m_username);
    lobbyWindow->show();
    this->destroy();
    
}

void MenuWindow::GetBestScoreAndLastMatches()
{
    QString usernameString = QString(m_username.c_str());
    ui.usernameLabel->setText(usernameString);
    std::pair<uint16_t, std::list<int16_t>> bestScoreAndLastMatchesPoints = m_client.GetBestScoreAndLastMatchesPoints(m_username);
    m_bestScore = bestScoreAndLastMatchesPoints.first;
    m_lastMatchesPoints = bestScoreAndLastMatchesPoints.second;
    ui.scoreList->addItem("Best Score: " + QString::number(m_bestScore));
    for (const uint16_t& points : m_lastMatchesPoints) {
        ui.scoreList->addItem(QString::number(points));
    }

    ui.scoreList->setMaximumHeight(6 * ui.scoreList->sizeHintForRow(0));
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

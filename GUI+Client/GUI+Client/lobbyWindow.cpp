#include "LobbyWindow.h"
#include "MenuWindow.h"
#include "GameWindow.h"
#include <thread>
#include <chrono>
#include <qtimer.h>

LobbyWindow::LobbyWindow(const std::string& username, QWidget* parent):
	QMainWindow(parent),
	m_username(username)
{
    ui.setupUi(this);
    m_client.Send_UsernameForLobby(username);

    connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::StartGameButton_Clicked);
    connect(ui.difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Difficulty_Changed);
    connect(ui.languageBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Language_Changed);

    for (uint8_t i = 0; i < ui.playersListWidget->count(); ++i)
    {
	    ui.playersListWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    gameStatusTimer = new QTimer(this);
    connect(gameStatusTimer, &QTimer::timeout, this, &LobbyWindow::GameStartThread);
	connect(gameStatusTimer, &QTimer::timeout, this, &LobbyWindow::StartUpdatingThread);
    gameStatusTimer->start(2000);
    GameStartThread();
    StartUpdatingThread();
}
void LobbyWindow::GameStartThread()
{
                
				m_GameStart = m_client.Return_GameStart();
				if (m_GameStart)
				{
					emit GameStarted();
				}
                
    

}

void LobbyWindow::StartUpdatingThread()
{
    
            m_players = m_client.Return_PlayersVector(m_username);

            if (m_players.size() == 1)
				m_IsLeader = true;
            emit PlayerJoinedLobby();
            m_difficulty = m_client.Return_GameDifficulty();
            m_language = m_client.Return_GameLanguage();
            emit PlayerChangedDifficulty();
            emit PlayerChangedLanguage();
    
}

void LobbyWindow::StopUpdatingThread()
{
    m_stopThread = false;
}

LobbyWindow::~LobbyWindow()
{
	this->destroy();
	StopUpdatingThread();
}

void LobbyWindow::GameStarted()
{
	gameStatusTimer->stop();
    auto* gameWindow = new GameWindow(m_username);
    gameWindow->show();
    this->destroy();
}

void LobbyWindow::StartGameButton_Clicked()
{
    if (m_IsLeader)
    {
    m_client.Send_StartGame_Signal();
    }

}

void LobbyWindow::UpdatePlayersListWidget(QListWidget* listWidget)
{
    listWidget->clear();
    for (const std::string& playerName:m_players) 
    {
        listWidget->addItem(QString(playerName.c_str()));
    }

}
void LobbyWindow::PlayerJoinedLobby()
{
    UpdatePlayersListWidget(ui.playersListWidget);
}

void LobbyWindow::Difficulty_Changed()
{
    m_difficulty = DIFFICULTY_MAP.at(ui.difficultyBox->currentText().toUtf8().constData());
    m_client.Send_GameDifficulty(m_difficulty);
}
void LobbyWindow::Language_Changed()
{
    m_language = DIFFICULTY_MAP.at(ui.languageBox->currentText().toUtf8().constData());
    m_client.Send_GameLanguage(m_language);
}

void LobbyWindow::PlayerChangedDifficulty()
{
	ui.difficultyBox->setCurrentIndex(m_difficulty);
}

void LobbyWindow::PlayerChangedLanguage()
{
    ui.languageBox->setCurrentIndex(m_language);
}



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
    m_stopThread.store(true);
    ui.setupUi(this);
    m_client.Send_UsernameForLobby(username);

    connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::StartGameButton_Clicked);
    connect(ui.difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Difficulty_Changed);
    connect(ui.languageBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Language_Changed);

    for (uint8_t i = 0; i < ui.playersListWidget->count(); ++i)
    {
	    ui.playersListWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    GameStartThread();
    StartUpdatingThread();
}
void LobbyWindow::GameStartThread()
{
    std::thread updateThread2([this]()
        {
            while (m_stopThread)
            {
				m_GameStart = m_client.Return_GameStart();
				if (m_GameStart)
				{
					emit GameStarted();
					m_stopThread.store(false);
				}
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

        });

    updateThread2.detach();
    

}
void LobbyWindow::StartUpdatingThread()
{
    std::thread updateThread([this]()
        {
            while (m_stopThread)
            {
                m_players = m_client.Return_PlayersVector(m_username);

                if (m_players.size() == 1)
                    m_IsLeader = true;

                emit PlayerJoinedLobby();
                m_difficulty = m_client.Return_GameDifficulty();
                m_language = m_client.Return_GameLanguage();
                emit PlayerChangedDifficulty();
                emit PlayerChangedLanguage();

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });

    updateThread.detach();
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
    QMetaObject::invokeMethod(this, [this]() {

    m_stopThread.store(false);
    auto* gameWindow = new GameWindow(m_username);
    gameWindow->show();
    this->destroy();

    }, Qt::QueuedConnection);

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
    QMetaObject::invokeMethod(this, [this]() {

    UpdatePlayersListWidget(ui.playersListWidget);

    }, Qt::QueuedConnection);
}

void LobbyWindow::Difficulty_Changed()
{
	const std::string difficultyChange = ui.difficultyBox->currentText().toUtf8().constData();
    m_difficulty = DIFFICULTY_MAP.at(difficultyChange);
    m_client.Send_GameDifficulty(m_difficulty);
}
void LobbyWindow::Language_Changed()
{
    const std::string languageChange = ui.languageBox->currentText().toUtf8().constData();
    m_language = LANGUAGE_MAP.at(languageChange);
    m_client.Send_GameLanguage(m_language);
}

void LobbyWindow::PlayerChangedDifficulty()
{
    QMetaObject::invokeMethod(this, [this]() {
        ui.difficultyBox->setCurrentIndex(m_difficulty);
        }, Qt::QueuedConnection);
}

void LobbyWindow::PlayerChangedLanguage()
{
    QMetaObject::invokeMethod(this, [this]() {
    ui.languageBox->setCurrentIndex(m_language);
    }, Qt::QueuedConnection);
}



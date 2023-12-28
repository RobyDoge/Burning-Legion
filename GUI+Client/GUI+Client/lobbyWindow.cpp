#include "LobbyWindow.h"
#include "MenuWindow.h"
#include "GameWindow.h"
#include <thread>
#include <chrono>

LobbyWindow::LobbyWindow(const std::string& username, QWidget* parent):
	QMainWindow(parent),
	m_username(username)
{
    m_stopThread.store(true);
    ui.setupUi(this);
    m_client.SendUsername(username);

    connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::StartGameButton_Clicked);
    connect(ui.difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Difficulty_Changed);
    connect(ui.languageBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LobbyWindow::Language_Changed);

    for (uint8_t i = 0; i < ui.playersListWidget->count(); ++i)
    {
	    ui.playersListWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    StartUpdatingThread();
}

void LobbyWindow::StartUpdatingThread()
{
    std::thread updateThread([this]() 
    {
        while (m_stopThread) 
        {
            m_players = m_client.GetPlayersVector(m_username);
            emit PlayerJoinedLobby();
            m_difficulty = m_client.GetDifficulty();
            m_language = m_client.GetLanguage();
            emit PlayerChangedDifficulty();
            emit PlayerChangedLanguage();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    updateThread.detach(); 
}

void LobbyWindow::StopUpdatingThread()
{
    m_stopThread.store(false);
}

LobbyWindow::~LobbyWindow()
{
	this->destroy();
	StopUpdatingThread();
}

void LobbyWindow::StartGameButton_Clicked()
{
    StopUpdatingThread();
    m_client.StartGame();
    auto* gameWindow = new GameWindow(m_username);
    gameWindow->show();
    this->destroy();

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
    m_client.SendDifficulty(m_difficulty);
}
void LobbyWindow::Language_Changed()
{
    m_language = DIFFICULTY_MAP.at(ui.languageBox->currentText().toUtf8().constData());
    m_client.SendLanguage(m_language);
}

void LobbyWindow::PlayerChangedDifficulty()
{
	ui.difficultyBox->setCurrentIndex(m_difficulty);
}

void LobbyWindow::PlayerChangedLanguage()
{
    ui.languageBox->setCurrentIndex(m_language);
}


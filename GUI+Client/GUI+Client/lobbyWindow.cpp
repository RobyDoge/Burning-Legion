#include "LobbyWindow.h"
#include "MenuWindow.h"
#include "GameWindow.h"
#include <thread>
#include <chrono>

void LobbyWindow::startUpdatingThread() {
    std::thread updateThread([this]() {
        while (stopThread) {

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

void LobbyWindow::stopUpdatingThread()
{
    stopThread.store(false);
}

LobbyWindow::LobbyWindow(std::string username,QWidget *parent)
	: m_username(username),QMainWindow(parent)
{
	stopThread.store(true);
	ui.setupUi(this);
	m_client.SendUsername(username);
	connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::startGameButton_clicked);
    connect(ui.difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &LobbyWindow::difficultyBoxIndexChanged);
    connect(ui.languageBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &LobbyWindow::languageBoxIndexChanged);
    for (int i = 0; i < ui.playersListWidget->count(); ++i) 
        ui.playersListWidget->item(i)->setTextAlignment(Qt::AlignCenter);  
    startUpdatingThread();
}

LobbyWindow::~LobbyWindow()
{
	this->destroy();
	stopUpdatingThread();
}

void LobbyWindow::startGameButton_clicked()
{
    stopUpdatingThread();
    m_client.StartGame();
    GameWindow* gameWindow = new GameWindow();
    gameWindow->show();
    this->destroy();

}

void LobbyWindow::UpdatePlayersListWidget(QListWidget* listWidget)
{
    listWidget->clear();
        
    for (const std::string& playerName:m_players) {
        listWidget->addItem(QString(playerName.c_str()));
    }

}
void LobbyWindow::PlayerJoinedLobby() {
    UpdatePlayersListWidget(ui.playersListWidget);
}

void LobbyWindow::difficultyBoxIndexChanged()
{
	m_difficulty = ConvertDifToInt(ui.difficultyBox->currentText().toUtf8().constData());
    m_client.SendDifficulty(m_difficulty);
}
void LobbyWindow::languageBoxIndexChanged()
{
    m_language = ConvertLangToInt(ui.languageBox->currentText().toUtf8().constData());
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
uint8_t LobbyWindow::ConvertDifToInt(const std::string& difficulty)
{
    if (difficulty == "Easy")
    {
        return 1;
    }
    else if (difficulty == "Normal")
    {
        return 2;
    }
    else if (difficulty == "Hard")
    {
        return 3;
    }
    return 0;

}
uint8_t LobbyWindow::ConvertLangToInt(const std::string& language)
{
    if (language == "Romanian")
    {
        return 1;
    }
    else if (language == "Spanish")
    {
        return 2;
    }
    else if (language == "English")
    {
        return 3;
    }
    return 0;
}


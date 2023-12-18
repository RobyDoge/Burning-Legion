#include "lobbyWindow.h"
#include <thread>
#include <chrono>


void LobbyWindow::startUpdatingThread() {
    std::thread updateThread([this]() {
        while (true) {

            m_players = m_client.GetPlayersVector(m_username);
            emit PlayerJoinedLobby();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        });

    updateThread.detach(); 
}
void LobbyWindow::stopUpdatingThread()
{
    stopThread.store(true);
}
LobbyWindow::LobbyWindow(std::string username,QWidget *parent)
	: m_username(username),QMainWindow(parent)
{
	ui.setupUi(this);
	m_client.SendUsername(username);
	connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::startGameButton_clicked);
    connect(ui.difficultyBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &LobbyWindow::difficultyBoxIndexChanged);
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
    m_difficulty = ui.difficultyBox->currentText();
    GameWindow* gameWindow = new GameWindow();
    gameWindow->show();

    stopUpdatingThread();
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
	m_difficulty = ui.difficultyBox->currentText();
 
    m_client.SendDifficulty(ConvertToInt(m_difficulty.toUtf8().constData()));
}

uint8_t LobbyWindow::ConvertToInt(const std::string& difficulty)
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
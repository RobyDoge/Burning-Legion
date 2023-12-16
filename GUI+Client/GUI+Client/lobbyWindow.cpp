#include "lobbyWindow.h"

LobbyWindow::LobbyWindow(std::string username,QWidget *parent)
	: m_username(username),QMainWindow(parent)
{
	ui.setupUi(this);
	m_client.SendUsername(m_username);
	connect(ui.startGameButton, &QPushButton::clicked, this, &LobbyWindow::startGameButton_clicked);
    for (int i = 0; i < ui.playersListWidget->count(); ++i) 
        ui.playersListWidget->item(i)->setTextAlignment(Qt::AlignCenter);  
}

LobbyWindow::~LobbyWindow()
{
	this->destroy();
}

void LobbyWindow::startGameButton_clicked()
{
    m_difficulty = ui.difficultyBox->currentText();
    GameWindow* gameWindow = new GameWindow();
    gameWindow->show();
    this->destroy();
}

void LobbyWindow::UpdatePlayersListWidget(QListWidget* listWidget)
{
    listWidget->clear();
    //std::vector<std::string> players = client.FetchPlayersInLobby();
    //if(m_players.size()==1) the first player that joins the lobby becomes the admin
        
    for (const std::string& playerName:m_players) {
        listWidget->addItem(QString::fromStdString(playerName));
    }

}
void LobbyWindow::PlayerJoinedLobby() {
	m_players = m_client.GetPlayersVector();
    UpdatePlayersListWidget(ui.playersListWidget);
}
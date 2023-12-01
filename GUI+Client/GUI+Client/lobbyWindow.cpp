#include "lobbyWindow.h"

LobbyWindow::LobbyWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
    //add players whenever they join a lobby
    UpdatePlayersListWidget(ui.playersListWidget);
}
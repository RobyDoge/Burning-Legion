#include "EndGameWindow.h"
#include "MenuWindow.h"
#include "Client.h"

EndGameWindow::EndGameWindow(const std::string& username,QWidget *parent)
	: QMainWindow(parent), m_username(username)
{
	ui.setupUi(this);
    connect(ui.backButton, &QPushButton::clicked, this, &EndGameWindow::BackButton_Clicked);
    m_players = Client::Return_SortedPlayers();
	DisplayPlayers();
}

void EndGameWindow::DisplayPlayers() const
{
    ui.endPlayersList->clear(); // Clear the existing content
    for (const auto& [playerName, playerScore] : m_players)
    {
        QString playerInfo = QString("%1: %2").arg(QString(playerName.c_str())).arg(playerScore);
        auto* item = new QListWidgetItem(playerInfo);
        ui.endPlayersList->addItem(item);
    }
}
void EndGameWindow::BackButton_Clicked()
{
    if(Client::Return_LeaveGameResponse(m_username)!=400)
    {
	    auto* menuWindow = new MenuWindow(std::move(m_username));
    	menuWindow->show();
    	this->close();
        return;
    }
    BackButton_Clicked();

}
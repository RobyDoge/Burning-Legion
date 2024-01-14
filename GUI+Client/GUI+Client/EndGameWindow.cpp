#include "EndGameWindow.h"
#include "MenuWindow.h"
EndGameWindow::EndGameWindow(QWidget *parent)
	: QMainWindow(parent)
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

}
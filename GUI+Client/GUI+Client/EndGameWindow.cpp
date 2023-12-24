#include "EndGameWindow.h"

EndGameWindow::EndGameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	CalculateWinner();
	DisplayPlayers();
}

EndGameWindow::~EndGameWindow()
{}

void EndGameWindow::CalculateWinner() const
{
    auto it = std::max_element(m_players.begin(), m_players.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    if (it != m_players.end())
    {
        std::string winnerName = it->first;
		QString winnerText = QString(winnerName.c_str());
        ui.winnerLabel->setText(winnerText); // Set the winner label
    }
    else
    {
        ui.winnerLabel->setText("No winner");
    }
}

void EndGameWindow::DisplayPlayers() const
{
    ui.endPlayersList->clear(); // Clear the existing content

    for (const auto& player : m_players)
    {
        QString playerInfo = QString("%1: %2").arg(QString(player.first.c_str())).arg(player.second);
        QListWidgetItem* item = new QListWidgetItem(playerInfo);
        ui.endPlayersList->addItem(item);
    }
}

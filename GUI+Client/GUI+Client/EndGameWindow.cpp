#include "EndGameWindow.h"
#include "MenuWindow.h"
EndGameWindow::EndGameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    connect(ui.backButton, &QPushButton::clicked, this, &EndGameWindow::BackButton_Clicked);
    m_playersPoints = m_client.Return_PlayersEndGamePoints();
    m_playersNames = m_client.Return_PlayersNames();
    m_players.reserve(m_playersPoints.size()); // Alocare spațiu pentru eficiență

    std::transform(m_playersPoints.begin(), m_playersPoints.end(), m_playersNames.begin(), std::back_inserter(m_players),
        [](float point, const std::string& name) {
            return std::make_pair(name, static_cast<int>(point));
        });


	DisplayPlayers();
}


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
    CalculateWinner();
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
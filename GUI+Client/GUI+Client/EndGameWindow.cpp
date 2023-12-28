#include "EndGameWindow.h"
#include "MenuWindow.h"
EndGameWindow::EndGameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    connect(ui.backButton, &QPushButton::clicked, this, &EndGameWindow::BackButton_Clicked);
	CalculateWinner();
	DisplayPlayers();
}


void EndGameWindow::CalculateWinner() const
{
  //  auto it = std::max_element(m_players.begin(), m_players.end(),
  //      [](const auto& a, const auto& b) { return a.second < b.second; });

  //  if (it != m_players.end())
  //  {
  //      std::string winnerName = it->first;
		//QString winnerText = QString(winnerName.c_str());
  //      ui.winnerLabel->setText(winnerText); // Set the winner label
  //  }
  //  else
  //  {
  //      ui.winnerLabel->setText("No winner");
  //  }
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
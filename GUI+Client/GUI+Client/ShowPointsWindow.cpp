#include "ShowPointsWindow.h"

ShowPointsWindow::ShowPointsWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	DisplayPlayers();
	ui.wordLabel->setText(QString(m_client.Return_WordToBeGuessed().c_str()));
}

ShowPointsWindow::~ShowPointsWindow()
{}

void ShowPointsWindow::SortPlayers()
{
	std::sort(m_players.begin(), m_players.end(), [](const std::pair<std::string, uint16_t>& a, const std::pair<std::string, uint16_t>& b) {
		return a.second > b.second; 
		});
}

void ShowPointsWindow::DisplayPlayers() 
{
	SortPlayers();
	ui.roundPlayersList->clear(); 

	for (const auto& player : m_players)
	{
		QString playerInfo = QString("%1: %2").arg(QString(player.first.c_str())).arg(player.second);
		QListWidgetItem* item = new QListWidgetItem(playerInfo);
		ui.roundPlayersList->addItem(item);
	}
}

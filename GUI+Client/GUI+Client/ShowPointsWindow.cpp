#include "ShowPointsWindow.h"
#include "Client.h"

ShowPointsWindow::ShowPointsWindow(QWidget *parent)
	:QMainWindow(parent)
{
	ui.setupUi(this);

	ui.wordLabel->setText(QString(Client::Return_WordToBeGuessed().c_str()));
	const auto& playersPoints = Client::Return_PlayersPoints();
	const auto& playersNames = Client::Return_PlayersNames();
	m_players.reserve(playersPoints.size());
	std::ranges::transform(playersPoints, playersNames, std::back_inserter(m_players),
	                       [](const int point, const std::string& name)
	                       {
		                       return std::make_pair(name, point);
	                       });
	DisplayPlayers();
}

void ShowPointsWindow::SortPlayers()
{
	std::ranges::sort(m_players, [](const auto& a, const auto& b) {
		return a.second > b.second; 
		});
}

void ShowPointsWindow::DisplayPlayers() 
{
	SortPlayers();
	ui.roundPlayersList->clear(); 

	for (const auto& [playerName, playerScore] : m_players)
	{
		QString playerInfo = QString("%1: %2").arg(QString(playerName.c_str())).arg(playerScore);
		const auto item = new QListWidgetItem(playerInfo);
		ui.roundPlayersList->addItem(item);
	}
}

#include "ShowPointsWindow.h"

ShowPointsWindow::ShowPointsWindow(QWidget *parent)
	:QMainWindow(parent)
{
	ui.setupUi(this);
	DisplayPlayers();
	ui.wordLabel->setText(QString(m_client.Return_WordToBeGuessed().c_str()));
	m_playersPoints =m_client.Return_PlayersPoints();
	m_playersNames = m_client.Return_PlayersNames();
	m_players.reserve(m_playersPoints.size()); // Alocare spațiu pentru eficiență

	std::transform(m_playersPoints.begin(), m_playersPoints.end(), m_playersNames.begin(), std::back_inserter(m_players),
		[](float point, const std::string& name) {
			return std::make_pair(name, static_cast<int>(point));
		});
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

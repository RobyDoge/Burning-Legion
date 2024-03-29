#include "EndRoundWindow.h"
#include "client.h"
EndRoundWindow::EndRoundWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    connect(ui.nextButton, &QPushButton::clicked, this, &EndRoundWindow::nextButton_clicked);
    DisplayPlayers();
    ui.wordLabel->setText(QString(m_client.GetWordToBeGuessed().c_str()));

}

EndRoundWindow::~EndRoundWindow()
{}

void EndRoundWindow::SortPlayers() const
{
    std::sort(m_players.begin(), m_players.end(), [](const std::pair<std::string, uint16_t>& a, const std::pair<std::string, uint16_t>& b) {
        return a.second > b.second; // Sort in descending order of scores
        });
}

void EndRoundWindow::DisplayPlayers() const
{
    SortPlayers();
    ui.roundPlayersList->clear(); // Clear the existing content

    for (const auto& player : m_players)
    {
        QString playerInfo = QString("%1: %2").arg(QString(player.first.c_str())).arg(player.second);
        QListWidgetItem* item = new QListWidgetItem(playerInfo);
        ui.roundPlayersList->addItem(item);
    }
}
void EndRoundWindow::nextButton_clicked()
{
}
#include "MenuWindow.h"
#include "LobbyWindow.h"
#include "Client.h"
#include "ShowImagesWindow.h"

MenuWindow::MenuWindow(const std::string& username,QWidget* parent)
    : QMainWindow(parent) , m_username (username)
{
    ui.setupUi(this);
   
    connect(ui.createLobbyButton, &QPushButton::clicked, this, &MenuWindow::CreateLobbyButton_Clicked);
    connect(ui.joinLobbyButton, &QPushButton::clicked, this, &MenuWindow::JoinLobbyButton_Clicked);
    connect(ui.SeeDrawings1, &QPushButton::clicked, this, &MenuWindow::SeeDrawingsButton1_Pushed);
    connect(ui.SeeDrawings2, &QPushButton::clicked, this, &MenuWindow::SeeDrawingsButton2_Pushed);
    connect(ui.SeeDrawings3, &QPushButton::clicked, this, &MenuWindow::SeeDrawingsButton3_Pushed);
    connect(ui.SeeDrawings4, &QPushButton::clicked, this, &MenuWindow::SeeDrawingsButton4_Pushed);
    connect(ui.SeeDrawings5, &QPushButton::clicked, this, &MenuWindow::SeeDrawingsButton5_Pushed);

    ui.SeeDrawings1->setVisible(false);
    ui.SeeDrawings2->setVisible(false);
    ui.SeeDrawings3->setVisible(false);
    ui.SeeDrawings4->setVisible(false);
    ui.SeeDrawings5->setVisible(false);

	GetBestScoreAndLastMatches();
}

void MenuWindow::OpenLobbyWindow()
{

    auto* lobbyWindow = new LobbyWindow(std::move(m_username));
    lobbyWindow->show();
    this->destroy();
}

void MenuWindow::SeeDrawingsButton1_Pushed()
{
	if (ui.SeeDrawings1->isVisible())
	{
		ShowImagesWindow* showImagesWindow = new ShowImagesWindow(m_imagesGame1,this);
		showImagesWindow->show();
		this->hide();
	}
}
void MenuWindow::SeeDrawingsButton2_Pushed()
{
	if (ui.SeeDrawings2->isVisible())
	{
		ShowImagesWindow* showImagesWindow = new ShowImagesWindow(m_imagesGame2, this);
		showImagesWindow->show();
	}
}
void MenuWindow::SeeDrawingsButton3_Pushed()
{
	if (ui.SeeDrawings3->isVisible())
	{
		ShowImagesWindow* showImagesWindow = new ShowImagesWindow(m_imagesGame3, this);
		showImagesWindow->show();
	}
}
void MenuWindow::SeeDrawingsButton4_Pushed()
{
	if (ui.SeeDrawings4->isVisible())
	{
		ShowImagesWindow* showImagesWindow = new ShowImagesWindow(m_imagesGame4, this);
		showImagesWindow->show();
	}
}
void MenuWindow::SeeDrawingsButton5_Pushed()
{
	if (ui.SeeDrawings5->isVisible())
	{
		ShowImagesWindow* showImagesWindow = new ShowImagesWindow(m_imagesGame5, this);
		showImagesWindow->show();
	}
}
void MenuWindow::GetBestScoreAndLastMatches()
{
	const auto usernameString = QString(m_username.c_str());
    ui.usernameLabel->setText(usernameString);
    auto games = Client::Return_Last5Games(m_username);
	ui.scoreList->clear();
	int index = 1;
	for (const auto& game : games)
	{
        QString MatchInfo = QString("%1: %2: %3").arg(QString("Match")).arg(QString::number(index)).arg(QString::number(game.first));
        QListWidgetItem* item = new QListWidgetItem(MatchInfo);
		switch (index)
		{
		case 1:
			ui.SeeDrawings1->setVisible(true);
			break;
		case 2:
			ui.SeeDrawings2->setVisible(true);
			break;
		case 3:
			ui.SeeDrawings3->setVisible(true);
			break;
		case 4:
			ui.SeeDrawings4->setVisible(true);
			break;
		case 5:
			ui.SeeDrawings5->setVisible(true);
			break;
		}
        ui.scoreList->addItem(item);
		index++;
	}

}

void MenuWindow::CreateLobbyButton_Clicked()
{
    if(Client::Send_CreateLobby_Signal(true)==200)
		OpenLobbyWindow();
}

void MenuWindow::JoinLobbyButton_Clicked()
{
	if (Client::Send_CreateLobby_Signal(false) == 200)
		OpenLobbyWindow();
}

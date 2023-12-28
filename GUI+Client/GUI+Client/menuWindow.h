#pragma once

#include <QMainWindow>
#include <QString>
#include "ui_menuWindow.h"
#include "LobbyWindow.h"
#include "Client.h"
#include <list>

class MenuWindow : public QMainWindow
{

public:
	MenuWindow(std::string username , QWidget *parent = nullptr);
	~MenuWindow() override = default;

private:
	void OpenLobbyWindow();

	//this function needs to be updated after the saving of drawings are done
	//and it should be split into multiple functions
	void GetBestScoreAndLastMatches();

private slots:
	void CreateLobbyButton_Clicked();
	void JoinLobbyButton_Clicked();

private:
	Ui::MenuWindowClass ui;
	QString m_code{};  //not in use
	std::string m_username{};
	uint16_t m_bestScore{};
	std::list<int16_t> m_lastMatchesPoints{};
	Client m_client{};
};

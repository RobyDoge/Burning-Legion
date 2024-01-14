#pragma once

#include <QMainWindow>
#include <QString>
#include "ui_menuWindow.h"
#include <list>

class MenuWindow : public QMainWindow
{

public:
	MenuWindow(const std::string& username , QWidget *parent = nullptr);
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
	std::string m_username{};
	//those should be updated after the request for the best score and last matches is implemented
	/*uint16_t m_bestScore{};
	std::list<int16_t> m_lastMatchesPoints{};*/
};

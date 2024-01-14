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
	void SeeDrawingsButton1_Pushed();
	void SeeDrawingsButton2_Pushed();
	void SeeDrawingsButton3_Pushed();
	void SeeDrawingsButton4_Pushed();
	void SeeDrawingsButton5_Pushed();


private:
	Ui::MenuWindowClass ui;
	std::string m_username{};
	std::tuple<std::string, std::string, std::string, std::string> m_imagesGame1;
	std::tuple<std::string, std::string, std::string, std::string> m_imagesGame2;
	std::tuple<std::string, std::string, std::string, std::string> m_imagesGame3;
	std::tuple<std::string, std::string, std::string, std::string> m_imagesGame4;
	std::tuple<std::string, std::string, std::string, std::string> m_imagesGame5;

	//those should be updated after the request for the best score and last matches is implemented
	/*uint16_t m_bestScore{};
	std::list<int16_t> m_lastMatchesPoints{};*/
};

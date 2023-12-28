#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <list>
#include<QByteArray>
class Client
{
public:

	long GetLoginResponse(const std::string& username, const std::string& password);
	long ConfirmUsernameAvailable(const std::string& username);
	long AddUser(const std::string& username, const std::string& password);
	void SendUsername(const std::string& username);
	void SendDifficulty(uint8_t difficulty);
	void SendLanguage(uint8_t language);
	void sendDrawing(const QByteArray& drawingData);
	std::pair<uint16_t, std::list< int16_t> > GetBestScoreAndLastMatchesPoints(const std::string& username);
	std::vector<std::string> GetPlayersVector(const std::string& username);
	uint8_t GetDifficulty();
	uint8_t GetLanguage();
	std::string GetWordToBeGuessed();
	std::string GetDrawer();
	std::string SendPlayerMessage(const std::string& message);
	uint8_t GetDrawerPosition();
	bool GetGameStatus();
	bool GetTurnStatus();
	void StartGame();
	void StartTurn();
	void CreateLobby();

private:

};
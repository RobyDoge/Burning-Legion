#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <list>
#include<QByteArray>
class Client
{
public:

	long Return_LoginResponse(const std::string& username, const std::string& password);
	long Return_UsernameAvailability(const std::string& username);
	long Return_CreateUserInDatabase(const std::string& username, const std::string& password);
	void Send_UsernameForLobby(const std::string& username);
	void Send_GameDifficulty(uint8_t difficulty);
	void Send_GameLanguage(uint8_t language);
	void Send_Drawing(const QByteArray& drawingData);

	//this fucntion should be modified and split once the drawing saving is implemented
	std::pair<uint16_t, std::list< int16_t> > GetBestScoreAndLastMatchesPoints(const std::string& username);
	std::vector<std::string> Return_PlayersVector(const std::string& username);
	uint8_t Return_GameDifficulty();
	uint8_t Return_GameLanguage();
	std::string Return_WordToBeGuessed();
	std::string Return_DrawerName();
	std::string Return_PlayerGuessResponse(const std::string& message);
	uint8_t Return_DrawerPosition();
	bool Return_GameStatus();
	bool Return_TurnStatus();
	void Send_StartGame_Signal();
	void StartTurn();
	void Send_CreateLobby_Signal();

private:

};
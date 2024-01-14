#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <list>
#include <QByteArray>

class Client
{
public:

	static long Return_LoginResponse(const std::string& username, const std::string& password);
	static long Return_UsernameAvailability(const std::string& username);
	static long Return_CreateUserInDatabase(const std::string& username, const std::string& password);

	static void Send_UsernameForLobby(const std::string& username);
	static void Send_GameDifficulty(uint8_t difficulty);
	static void Send_GameLanguage(uint8_t language);
	static void Send_Drawing(const std::string& drawingData);
	static void Send_PlayerGuess(const std::string& message);

	//this fucntion should be modified and split once the drawing saving is implemented
	static std::pair<uint16_t, std::list< int16_t> > GetBestScoreAndLastMatchesPoints(const std::string& username);
	static std::vector<std::string> Return_PlayersVector(const std::string& username);
	static uint8_t Return_GameDifficulty();
	static uint8_t Return_GameLanguage();
	static std::string Return_Drawing();
	static std::string Return_WordToBeGuessed();
	static std::string Return_DrawerName();
	static std::string Return_PlayerGuessResponse(const std::string& message, const std::string& guesser);
	static std::string Return_OtherPlayerGuess();
	static std::vector<uint16_t> Return_PlayersPoints();
	static std::vector<std::string> Return_PlayersNames();
	static std::vector<uint16_t> Return_PlayersEndGamePoints();
	static uint8_t Return_DrawerPosition();
	static bool Return_GameStatus();
	static void Send_StartGame_Signal();
	static void Send_CreateLobby_Signal();
	static bool Return_GameStart();
	static int Return_CurrentTime();
	static std::vector<std::pair<std::string, uint16_t >> Return_SortedPlayers();
};
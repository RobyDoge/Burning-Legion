#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <list>

class Client
{
public:

	long GetLoginResponse(const std::string& username, const std::string& password);
	long ConfirmUsernameAvailable(const std::string& username);
	long AddUser(const std::string& username, const std::string& password);
	void SendUsername(const std::string& username);
	void SendDifficulty(uint8_t difficulty);
	std::pair<uint16_t, std::list< int16_t> > GetBestScoreAndLastMatchesPoints(const std::string& username);
	std::vector<std::string> GetPlayersVector(const std::string& username);
	
	//std::vector<std::string> FetchPlayersInLobby();  //This is supposed to fetch the usernames of all players in lobby
private:

};


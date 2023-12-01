#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>

class Client
{
public:

	long GetLoginResponse(const std::string& username, const std::string& password);
	long ConfirmUsernameAvailable(const std::string& username);
	long AddUser(const std::string& username, const std::string& password);
	//std::vector<std::string> Client::FetchPlayersInLobby()  //This is supposed to fetch the usernames of all players in lobby
private:


};


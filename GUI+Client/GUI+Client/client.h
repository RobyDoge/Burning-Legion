#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>

class Client
{
public:

	long GetLoginResponse( std::string username,  std::string password);
	long ConfirmUsernameAvailable( std::string username);

private:

	//cpr::Response m_loginResponse = cpr::Get(cpr::Url{ "http://localhost:69420/login" });
	//cpr::Response m_signupResponse = cpr::Get(cpr::Url{ "http://localhost:69420/signup" });

};


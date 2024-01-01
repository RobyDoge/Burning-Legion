#include "Client.h"


long Client::Return_LoginResponse(const std::string& username, const std::string & password)
{
    //Create a json to send it to the server
    const std::string json_data = R"({"username": ")" + username + R"(", "password": ")" + password + R"("})";

    //Create a post request to the server and post the json 
    const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/login" },
                                    cpr::Header{ {"Content-Type", "application/json"} },
                                    cpr::Body{ json_data });

    //Wait for response and return it
    return response.status_code;
}

long Client::Return_UsernameAvailability(const std::string& username) {
	const std::string json_data = R"({"username": ")" + username + R"("})";

	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/signup" },
	                                cpr::Header{ {"Content-Type", "application/json"} },
	                                cpr::Body{ json_data });

    return response.status_code;
}

long Client::Return_CreateUserInDatabase(const std::string& username, const std::string& password)
{
	const std::string json_data = R"({"username": ")" + username + R"(", "password": ")" + password + R"("})";

	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/signupaccount" },
	                                cpr::Header{ {"Content-Type", "application/json"} },
	                                cpr::Body{ json_data });

    return response.status_code;
}

//should be redone
//std::pair<uint16_t, std::list< int16_t>> Client::GetBestScoreAndLastMatchesPoints(const std::string& username) 
//{
//    std::string json_data = R"({"username": ")" + username + R"("})";
//
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/mainMenu" },
//        cpr::Header{ {"Content-Type", "application/json"} },
//        cpr::Body{ json_data });
//
//    auto scores = crow::json::load(response.text);
//    bool ok = true;
//    uint16_t bestScore;
//    std::list<int16_t> list;
//    for (const auto& score : scores)
//    {
//		if (ok) { bestScore = score["bestscores"].i(); ok = false; }
//        else
//		list.push_back(score["points"].i());
//    }
//	
//	return std::make_pair(bestScore, list);
//}


void Client::Send_UsernameForLobby(const std::string& username)
{
	const std::string json_data = R"({"username": ")" + username + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbyGetUsers" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });
}

void Client::Send_GameDifficulty(const uint8_t difficulty)
{
	const std::string json_data = R"({"difficulty": ")" + std::to_string(difficulty) + R"("})";

	auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbySetDifficulty" },
		cpr::Header{ {"Content-Type", "application/json"} },
		cpr::Body{ json_data });
}

void Client::Send_GameLanguage(const uint8_t language)
{
	const std::string json_data = R"({"language": ")" + std::to_string(language) + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbySetLanguage" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });
}


std::pair<uint16_t, std::list<int16_t>> Client::GetBestScoreAndLastMatchesPoints(const std::string& username)
{
	return std::pair<uint16_t, std::list<int16_t>>();
}

std::vector<std::string> Client::Return_PlayersVector(const std::string& username)
{
	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbySendUsers" },
	                                cpr::Header{ {"Content-Type", "application/json"} });

	const auto usersReceived = crow::json::load(response.text);

    std::vector<std::string> users;
    for (const auto& user : usersReceived)
    {

        users.push_back(user["user"].s());
    }

    return users;
}

uint8_t Client::Return_GameDifficulty()
{
    const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbyGetDifficulty" },
        cpr::Header{ {"Content-Type", "application/json"} });

	return crow::json::load(response.text)["difficulty"].i();
}

uint8_t Client::Return_GameLanguage()
{
	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbyGetLanguage" },
	                                cpr::Header{ {"Content-Type", "application/json"} });

    return crow::json::load(response.text)["language"].i();
}

std::string Client::Return_WordToBeGuessed()
{
	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startTurn/WordToBeGuessed" },
	                                cpr::Header{ {"Content-Type", "application/json"} });

    return crow::json::load(response.text)["WordToBeGuessed"].s();
}

std::string Client::Return_DrawerName()
{
	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startTurn/DrawerName" },
	                                cpr::Header{ {"Content-Type", "application/json"} });

    return crow::json::load(response.text)["DrawerName"].s();
}

std::string Client::Return_PlayerGuessResponse(const std::string& message)
{
	const std::string json_data = R"({"message": ")" + message + R"("})";

	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startTurn/GetMessage" },
	                                cpr::Header{ {"Content-Type", "application/json"} },
	                                cpr::Body{ json_data });

    return crow::json::load(response.text)["message"].s();


}

uint8_t Client::Return_DrawerPosition()
{
	const auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startTurn/DrawerPosition" },
	                                cpr::Header{ {"Content-Type", "application/json"} });
    return crow::json::load(response.text)["DrawerPosition"].i();
}


bool Client::Return_GameStatus()
{
	if (const auto response = Post(cpr::Url{"http://localhost:18080/startGame/Return_GameStatus"},
	                               cpr::Header{{"Content-Type", "application/json"}});
		crow::json::load(response.text)["Status"].s() == "true")
	{
		return true;
	}
	return false;
}


void Client::Send_StartGame_Signal()
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startGame"},
        cpr::Header{ {"Content-Type", "application/json"} });

}

void Client::Send_CreateLobby_Signal()
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobby" },
        cpr::Header{ {"Content-Type", "application/json"} });
}
void Client::Send_Drawing(const QByteArray& drawingData)
{
    auto reponse = cpr::Post(cpr::Url{ "http://localhost:18080/drawingEndpoint" },
        cpr::Body{ drawingData.constData(), static_cast<size_t>(drawingData.size()) },
        cpr::Header{ {"Content-Type", "application/octet-stream"} });
}
//void Client::displayReceivedDrawing(const QByteArray& drawingData)
//{
//    QImage image;
//    if (image.loadFromData(drawingData, "PNG")) 
//    {
//        QPixmap pixmap = QPixmap::fromImage(image);
//
//        m_gameWindow->setReceivedDrawing(pixmap);
//    }
//}
#include "client.h"


long Client::GetLoginResponse(const std::string& username, const std::string & password)
{
    //Create a json to send it to the server
    std::string json_data = R"({"username": ")" + username + R"(", "password": ")" + password + R"("})";

    //Create a post request to the server and post the json 
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    //Wait for response and return it
    return response.status_code;
}

long Client::ConfirmUsernameAvailable(const std::string& username) {

    std::string json_data = R"({"username": ")" + username + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/signup" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    return response.status_code;
}

long Client::AddUser(const std::string& username, const std::string& password)
{
    std::string json_data = R"({"username": ")" + username + R"(", "password": ")" + password + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/signupaccount" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    return response.status_code;
}


std::pair<uint16_t, std::list< int16_t>> Client::GetBestScoreAndLastMatchesPoints(const std::string& username) 
{
    std::string json_data = R"({"username": ")" + username + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/mainMenu" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    auto scores = crow::json::load(response.text);
    bool ok = true;
    uint16_t bestScore;
    std::list<int16_t> list;
    for (const auto& score : scores)
    {
		if (ok) { bestScore = score["bestscores"].i(); ok = false; }
        else
		list.push_back(score["points"].i());
    }
	
	return std::make_pair(bestScore, list);
}


void Client::SendUsername(const std::string& username)
{

    std::string json_data = R"({"username": ")" + username + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbyGetUsers" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });


}

void Client::SendDifficulty(uint8_t difficulty)
{
	std::string json_data = R"({"difficulty": ")" + std::to_string(difficulty) + R"("})";

	auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbySetDifficulty" },
		cpr::Header{ {"Content-Type", "application/json"} },
		cpr::Body{ json_data });
}


std::vector<std::string> Client::GetPlayersVector(const std::string& username)
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbySendUsers" },
        cpr::Header{ {"Content-Type", "application/json"} });

    auto usersReceived = crow::json::load(response.text);

    std::vector<std::string> users;
    for (const auto& user : usersReceived)
    {

        users.push_back(user["user"].s());
    }

    return users;
}

uint8_t Client::GetDifficulty()
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/lobbyGetDifficulty" },
        cpr::Header{ {"Content-Type", "application/json"} });

	return crow::json::load(response.text)["difficulty"].i();
}

std::string Client::GetWordToBeGuessed()
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startRound/WordToBeGuessed" },
        cpr::Header{ {"Content-Type", "application/json"} });

    return crow::json::load(response.text)["WordToBeGuessed"].s();
}

std::string Client::GetDrawer()
{
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/startRound/Drawer" },
        cpr::Header{ {"Content-Type", "application/json"} });

    return crow::json::load(response.text)["Drawer"].s();
}

std::string Client::SendPlayerMessage(const std::string& message)
{
    std::string json_data = R"({"message": ")" + message + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/GetMessage" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    return crow::json::load(response.text)["messsage"].s();


}

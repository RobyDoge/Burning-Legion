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
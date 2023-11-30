#include "client.h"


long Client::GetLoginResponse(std::string username, std::string password)
{
    
    std::string json_data = R"({"username": ")" + username + R"(", "password": ")" + password + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    return response.status_code;
}

long Client::ConfirmUsernameAvailable( std::string username) {

    std::string json_data = R"({"username": ")" + username + R"("})";

    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/signup" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data });

    return response.status_code;
}
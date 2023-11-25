//#include "client.h"
//
//
//long Client::GetLoginResponse(const std::string& username, const std::string& password)
//{
//    cpr::Response response = cpr::Post(
//        cpr::Url{ "http://localhost:69420/login" },
//        cpr::Payload{
//            { "username", username },
//            { "password", password }
//        }
//    );
//
//    return response.status_code;
//}
//
//long Client::ConfirmUsernameAvailable(const std::string& username) {
//    cpr::Response response = cpr::Post(
//        cpr::Url{ "http://localhost:69420/signup" }, 
//        cpr::Payload{
//            { "username", username }
//        }
//    );
//
//    return response.status_code;
//}
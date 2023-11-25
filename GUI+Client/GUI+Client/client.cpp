//#include "client.h"
//
//
//void Client::GetLoginResponse(const std::string& username, const std::string& password) 
//{
//    cpr::Response response = cpr::Post(
//        cpr::Url{ "http://localhost:69420/login" },
//        cpr::Payload{
//            { "username", username },
//            { "password", password }
//        }
//    );
//
//    if (response.status_code == 200) {
//        std::cout << "Autentificare reușită\n";
//    }
//    else {
//        std::cout << "Autentificare eșuată\n";
//    }
//}
//

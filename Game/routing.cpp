﻿//#include "routing.h"
//#include "iostream"
//using namespace http;
//
//
//void Routing::Run(Dictionary& wordStorage/*, UserDateBase& userStorage*/)
//{
//	CROW_ROUTE(m_app, "/")([]() {
//		return "This is an example app of crow and sql-orm";
//		});
//
//    CROW_ROUTE(m_app, "/login").methods(crow::HTTPMethod::Post)(
//        [&userStorage](const crow::request& req) {
//            return HandleLogin(req, userStorage);
//        }
//    );
//    CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::Post)(
//        [&userDatabase](const crow::request& req) {
//            return isUsernameAvailable(req, userStorage)
//        }
//    );
//	m_app.port(69420).multithreaded().run();
//
//}
//
//crow::response Routing::HandleLogin(const crow::request& req, const UserStorage& userStorage) 
//{
//    // Se așteaptă ca datele să fie trimise în format JSON
//    auto json = crow::json::load(req.body);
//
//    if (!json) 
//    {
//        return crow::response(400, "Invalid JSON");
//    }
//
//    // Verificare autentificare
//    if (json["username"].s() != nullptr && json["password"].s() != nullptr)
//    {
//        std::string username = json["username"].s();
//        std::string password = json["password"].s();
//
//        if (userStorage.Authenticate(username, password))
//        {
//            return crow::response(200, "Autentificare reușită");
//        }
//        else
//        {
//            return crow::response(401, "Autentificare eșuată");
//        }
//    }
//    else 
//    {
//        return crow::response(400, "Username și password sunt necesare");
//    }
//}
//
//crow::response Routing::isUsernameAvailable(const crow::request& req, const UserStorage& userStorage) {
//    auto json = crow::json::load(req.body);
//
//    if (!json) {
//        return crow::response(400, "Invalid JSON");
//    }
//
//    if (json["username"].s() != nullptr) {
//        std::string username = json["username"].s();
//
//        if (userDatabase.AuthenticateUsername(username)) {
//            return crow::response(200, "Username is available");
//        }
//        else {
//            return crow::response(409, "Username is not available");
//        }
//    }
//    else {
//        return crow::response(400, "Username is required");
//    }
//
//}
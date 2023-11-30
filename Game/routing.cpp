#include "routing.h"
#include "iostream"
using namespace http;


void Routing::Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});


    CROW_ROUTE(m_app, "/login")
        .methods("POST"_method)
        ([&userStorage](const crow::request& req) {
        // Obține datele trimise de client
        auto jsonData = crow::json::load(req.body);
        if (!jsonData)
            return crow::response(400);

        std::string username = jsonData["username"].s();
        std::string password = jsonData["password"].s();

        // Verifică credențialele în baza de date (înlocuiește cu verificarea în baza ta de date)
        bool credentialsValid = userStorage.Authenticate(username, password);

        // Returnează un răspuns în funcție de rezultatul verificării
        if (credentialsValid) {
            return crow::response(200, "OK");
        }
        else {
            return crow::response(401, "Unauthorized");
        }
            });

    CROW_ROUTE(m_app, "/signup")
        .methods("POST"_method)
        ([&userStorage](const crow::request& req) {
        // Obține datele trimise de client
        auto jsonData = crow::json::load(req.body);
        if (!jsonData)
            return crow::response(400);

        std::string username = jsonData["username"].s();

        // Verifică credențialele în baza de date (înlocuiește cu verificarea în baza ta de date)
        bool credentialsValid = userStorage.CheckUsername(username);

        // Returnează un răspuns în funcție de rezultatul verificării
        if (credentialsValid) {
            return crow::response(200, "OK");
        }
        else {
            return crow::response(401, "Unauthorized");
        }
            });

	m_app.port(18080).multithreaded().run();

}

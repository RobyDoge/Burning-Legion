#include "Routing.h"
#include "ostream"

using namespace http;


void Routing::Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage)
{
	CROW_ROUTE(m_app, "/")([]()
	{
		return "This is an example app of crow and sql-orm";
	});


	CROW_ROUTE(m_app, "/login")
        .methods("POST"_method)
	                           ([&userStorage](const crow::request& req)
	                           {
		                           //Get the data that was sent from the client
		                           const auto jsonData = crow::json::load(req.body);
		                           if (!jsonData)
			                           return crow::response(400);

		                           const std::string username = jsonData["username"].s();
		                           const std::string password = jsonData["password"].s();

		                           //Check if the username and password exist in the database
		                           if (userStorage.Authenticate(username, password))
		                           {
			                           return crow::response(200, "OK");
		                           }
		                           return crow::response(401, "Unauthorized");
	                           });

	CROW_ROUTE(m_app, "/signup")
        .methods("POST"_method)
	                            ([&userStorage](const crow::request& req)
	                            {
		                            // Obține datele trimise de client
		                            const auto jsonData = crow::json::load(req.body);
		                            if (!jsonData)
			                            return crow::response(400);

		                            // Returnează un răspuns în funcție de rezultatul verificării
		                            if (const std::string username = jsonData["username"].s(); userStorage.CheckUsername(username))
		                            {
			                            return crow::response(200, "OK");
		                            }
		                            return crow::response(401, "Unauthorized");
	                            });


	CROW_ROUTE(m_app, "/signupaccount")
        .methods("POST"_method)
	                                   ([&userStorage](const crow::request& req)
	                                   {
		                                   // Obține datele trimise de client
		                                   const auto jsonData = crow::json::load(req.body);
		                                   if (!jsonData)
			                                   return crow::response(400);
		                                   userStorage.AddUser( jsonData["username"].s() , jsonData["password"].s());

		                                   return crow::response(200, "OK");
	                                   });

	CROW_ROUTE(m_app, "/lobbySetupUsers")
        .methods("POST"_method)
	                                     ([&userStorage, this](const crow::request& req)
	                                     {
		                                     // Obține datele trimise de client
		                                     const auto jsonData = crow::json::load(req.body);
		                                     if (!jsonData)
			                                     return crow::response(400);

		                                     m_lastUsername = jsonData["userid"].s();

		                                     // Returnează un răspuns simplu
		                                     return crow::response(200, "OK");
	                                     });

	m_app.port(18080).multithreaded().run();
}

std::string Routing::GetLastUsername() const
{
	return m_lastUsername;
}

bool Routing::GetGameStart() const
{
	return m_gameStart;
}

uint8_t Routing::GetDifficulty() const
{
	return m_difficulty;
}

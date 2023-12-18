#include "Routing.h"
#include "ostream"


using namespace server;


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
		                            if (const std::string username = jsonData["username"].s(); userStorage.
			                            CheckUsername(username))
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
		                                   userStorage.AddUser(jsonData["username"].s(), jsonData["password"].s());

		                                   return crow::response(200, "OK");
	                                   });

	CROW_ROUTE(m_app, "/mainMenu")
        .methods("POST"_method)
	                              ([&userStorage](const crow::request& req)
	                              {
		                              auto jsonData = crow::json::load(req.body);

		                              std::string username = jsonData["username"].s();

		                              uint16_t bestscores = userStorage.GetBestScore(username);
		                              std::deque<int16_t> lastmatches = userStorage.GetLastMatchesPoints(username);

		                              std::vector<crow::json::wvalue> responseJson;
		                              responseJson.push_back(crow::json::wvalue{{"bestscores", bestscores}});

		                              for (const auto& points : lastmatches)
		                              {
			                              responseJson.push_back(crow::json::wvalue{{"points", points}});
		                              }

		                              return crow::json::wvalue{responseJson};
	                              });
	CROW_ROUTE(m_app, "/lobbyGetUsers")
		.methods("POST"_method)
										([this](const crow::request& req)
											{
												const auto jsonData = crow::json::load(req.body);
												if (!jsonData)
													return crow::response(400);

												m_gameHandlers.AddUserToLobby ( jsonData["username"].s());
												
												return crow::response(200, "valid");
											});

	CROW_ROUTE(m_app, "/lobbySendUsers")
        .methods("POST"_method)
	                                     ([this](const crow::request& req)
	                                     {
		                                 
											 std::vector<crow::json::wvalue> responseJson;
											 std::vector<std::string> users = m_gameHandlers.GetUsersNames();
											 for (const auto& user : users)
											 {
												 std::cout << user;
												 responseJson.push_back(crow::json::wvalue{ {"user", user} });
											 }
											 return crow::json::wvalue{ responseJson };
	                                     });
	CROW_ROUTE(m_app, "/lobbyGetDifficulty")
		.methods("POST"_method)
										([this](const crow::request& req)
											{
												crow::json::wvalue responseJson=crow::json::wvalue{ {"difficulty", m_gameHandlers.GetDifficulty()}};
												return crow::json::wvalue{ responseJson };

											});

	CROW_ROUTE(m_app, "/lobbySetDifficulty")
		.methods("POST"_method)
										([this](const crow::request& req)
											{
												const auto jsonData = crow::json::load(req.body);
												if (!jsonData)
													return crow::response(400);
												m_gameHandlers.SetDifficulty(jsonData["difficulty"].i());
												return crow::response(200, "OK");
											});

	m_app.port(18080).multithreaded().run();
}
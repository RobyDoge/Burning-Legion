#include "Routing.h"
#include "ostream"


using namespace server;


void Routing::Run()
{
	CROW_ROUTE(m_app, "/")([]()
	{
		return "This is an example app of crow and sql-orm";
	});


	CROW_ROUTE(m_app, "/login")
        .methods("POST"_method)
	                           ([this](const crow::request& req)
	                           {
		                           //Get the data that was sent from the client
		                           const auto jsonData = crow::json::load(req.body);
		                           if (!jsonData)
			                           return crow::response(400);

		                           //Check if the username and password exist in the database
		                           if (m_userStorage.Authenticate(jsonData["username"].s(), jsonData["password"].s()))
		                           {
			                           return crow::response(200, "OK");
		                           }
		                           return crow::response(401, "Unauthorized");
	                           });

	CROW_ROUTE(m_app, "/signup")
        .methods("POST"_method)
	                            ([this](const crow::request& req)
	                            {
		                            // Obține datele trimise de client
		                            const auto jsonData = crow::json::load(req.body);
		                            if (!jsonData)
			                            return crow::response(400);

		                            // Returnează un răspuns în funcție de rezultatul verificării
		                            if (m_userStorage.CheckUsername(jsonData["username"].s()))
		                            {
			                            return crow::response(200, "OK");
		                            }
		                            return crow::response(401, "Unauthorized");
	                            });


	CROW_ROUTE(m_app, "/CreateUser")
        .methods("POST"_method)
	                                   ([this](const crow::request& req)
	                                   {
		                                   // Obține datele trimise de client
		                                   const auto jsonData = crow::json::load(req.body);
		                                   if (!jsonData)
			                                   return crow::response(400);
		                                   m_userStorage.AddUser(jsonData["username"].s(), jsonData["password"].s());

		                                   return crow::response(200, "OK");
	                                   });

	CROW_ROUTE(m_app, "/mainMenu")
        .methods("POST"_method)
	                              ([this](const crow::request& req)
	                              {
		                              const auto jsonData = crow::json::load(req.body);

		                              const std::string username = jsonData["username"].s();
									  std::vector<crow::json::wvalue> responseJson;

										//this need to be redone to send  vector of pairs {game score, the 4 images}

		                              /*uint16_t bestscores = m_userStorage.GetBestScore(username);
		                              std::deque<int16_t> lastmatches = m_userStorage.GetLastMatchesPoints(username);

		                              responseJson.push_back(crow::json::wvalue{{"bestscores", bestscores}});

		                              for (const auto& points : lastmatches)
		                              {
			                              responseJson.push_back(crow::json::wvalue{{"points", points}});
		                              }*/

		                              return crow::json::wvalue{responseJson};
	                              });

	CROW_ROUTE(m_app, "/lobby")
		.methods("POST"_method)
	                           ([this](const crow::request& req)
	                           {
		                           if (crow::json::load(req.body))
			                           return crow::response(400);

		                           m_gameHandlers.CreateLobby();
		                           return crow::response(200, "OK");
	                           });

	CROW_ROUTE(m_app, "/lobbyGetUsers")
		.methods("POST"_method)
	                                   ([this](const crow::request& req)
	                                   {
		                                   const auto jsonData = crow::json::load(req.body);
		                                   if (!jsonData)
			                                   return crow::response(400);

		                                   m_gameHandlers.AddUserToLobby(jsonData["username"].s());

		                                   return crow::response(200, "valid");
	                                   });

	CROW_ROUTE(m_app, "/lobbySendUsers")
        .methods("POST"_method)
	                                    ([this](const crow::request& req)
	                                    {
		                                    std::vector<crow::json::wvalue> responseJson;
		                                    const auto users = m_gameHandlers.GetUsersNames();
											m_usersNames = users;
		                                    for (const auto& userName : users)
		                                    {
			                                    std::cout << userName;
			                                    responseJson.push_back(crow::json::wvalue{{"user", userName}});
		                                    }
		                                    return crow::json::wvalue{responseJson};
	                                    });
	CROW_ROUTE(m_app, "/lobbyGetDifficulty")
		.methods("POST"_method)
	                                        ([this](const crow::request& req)
	                                        {
		                                        const auto responseJson = crow::json::wvalue{
			                                        {"difficulty", m_gameHandlers.GetDifficulty()}
		                                        };
		                                        return crow::json::wvalue{responseJson};
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

	CROW_ROUTE(m_app, "/lobbyGetLanguage")
		.methods("POST"_method)
	                                      ([this](const crow::request& req)
	                                      {
		                                      const auto responseJson = crow::json::wvalue{
			                                      {"language", m_gameHandlers.GetLanguage()}
		                                      };
		                                      return crow::json::wvalue{responseJson};
	                                      });

	CROW_ROUTE(m_app, "/lobbySetLanguage")
		.methods("POST"_method)
	                                      ([this](const crow::request& req)
	                                      {
		                                      const auto jsonData = crow::json::load(req.body);
		                                      if (!jsonData)
			                                      return crow::response(400);

		                                      m_gameHandlers.SetLanguage(jsonData["language"].i());
		                                      return crow::response(200, "Language set successfully");
	                                      });

	CROW_ROUTE(m_app, "/startGame")
		.methods("POST"_method)
	                               ([this](const crow::request& req)
	                               {
		                               if (crow::json::load(req.body))
			                               return crow::response(400);

		                               m_gameHandlers.StartGame();
		                               return crow::response(200, "OK");
	                               });
	CROW_ROUTE(m_app, "/startTurn/Return_CurrentTime")
		.methods("POST"_method)
	                                                  ([this](const crow::request& req)
	                                                  {
		                                                  const auto responseJson = crow::json::wvalue{
			                                                  {"CurrentTime", m_gameHandlers.GetTime()}
		                                                  };
		                                                  return crow::json::wvalue{responseJson};
	                                                  });

	CROW_ROUTE(m_app, "/startGame/Return_GameStatus")
		.methods("POST"_method)
	                                                 ([this](const crow::request& req)
	                                                 {
		                                                 std::string status;
		                                                 if (m_gameHandlers.GetGameStatus())
		                                                 {
			                                                 status = "true";
		                                                 }
		                                                 else
		                                                 {
			                                                 status = "false";
		                                                 }
		                                                 const auto responseJson = crow::json::wvalue{
			                                                 {"Status", status}
		                                                 };
		                                                 return crow::json::wvalue{responseJson};
	                                                 });
	CROW_ROUTE(m_app, "/startGame/Return_GameStart")
		.methods("POST"_method)
	                                                ([this](const crow::request& req)
	                                                {
		                                                std::string status;
		                                                if (m_gameHandlers.IsGameStarted())
		                                                {
			                                                status = "true";
		                                                }
		                                                else
		                                                {
			                                                status = "false";
		                                                }
		                                                const auto responseJson = crow::json::wvalue{
			                                                {"Start", status}
		                                                };
		                                                return crow::json::wvalue{responseJson};
	                                                });
	CROW_ROUTE(m_app, "/startTurn/DrawerPosition")
		.methods("POST"_method)
	                                              ([this](const crow::request& req)
	                                              {
		                                              const auto responseJson = crow::json::wvalue{
			                                              {"DrawerPosition", m_gameHandlers.GetDrawerPosition()}
		                                              };
		                                              return crow::json::wvalue{responseJson};
	                                              });
	CROW_ROUTE(m_app, "/startTurn/DrawerName")
		.methods("POST"_method)
	                                          ([this](const crow::request& req)
	                                          {
		                                          const auto responseJson = crow::json::wvalue{
			                                          {"DrawerName", m_gameHandlers.GetDrawerName()}
		                                          };
		                                          return crow::json::wvalue{responseJson};
	                                          });
	CROW_ROUTE(m_app, "/startTurn/WordToBeGuessed")
		.methods("POST"_method)
	                                               ([this](const crow::request& req)
	                                               {
		                                               const auto responseJson = crow::json::wvalue{
			                                               {"WordToBeGuessed", m_gameHandlers.GetWordToBeGuessed()}
		                                               };
		                                               return crow::json::wvalue{responseJson};
	                                               });

	CROW_ROUTE(m_app, "/startTurn/GetMessage")
		.methods("POST"_method)
	                                          ([this](const crow::request& req)
	                                          {
		                                          const auto jsonData = crow::json::load(req.body);
		                                          const auto message = m_gameHandlers.CheckMessage(
			                                          jsonData["message"].s(), jsonData["guesser"].s());
		                                          const auto responseJson = crow::json::wvalue
		                                          {
			                                          {"message", message}
		                                          };
		                                          return crow::json::wvalue{responseJson};
	                                          });
	CROW_ROUTE(m_app, "/startTurn/Set_PlayerGuess")
		.methods("POST"_method)
	                                               ([this](const crow::request& req)
	                                               {
		                                               const auto jsonData = crow::json::load(req.body);
		                                               m_gameHandlers.SetCurrentGuess(jsonData["guess"].s());
		                                               return crow::response(200, "OK");
	                                               });
	CROW_ROUTE(m_app, "/startTurn/Return_OtherPlayerGuess")
		.methods("POST"_method)
	                                                       ([this](const crow::request& req)
	                                                       {
		                                                       const auto responseJson = crow::json::wvalue{
			                                                       {"guess", m_gameHandlers.GetCurrentGuess()}
		                                                       };
		                                                       return crow::json::wvalue{responseJson};
	                                                       });


	CROW_ROUTE(m_app, "/startTurn/Return_DrawingData")
		.methods("POST"_method)
	                                                  ([this](const crow::request& req)
	                                                  {
		                                                  const auto responseJson = crow::json::wvalue{
			                                                  {"DrawingData", m_gameHandlers.GetDrawing()}
		                                                  };
		                                                  return crow::json::wvalue{responseJson};
	                                                  });


	CROW_ROUTE(m_app, "/startTurn/SendDrawing")
		.methods("POST"_method)
	                                           ([this](const crow::request& req)
	                                           {
		                                           const auto jsonData = crow::json::load(req.body);
		                                           if (!jsonData)
			                                           return crow::response(400);

		                                           m_gameHandlers.SetDrawing(jsonData["DrawingData"].s());
		                                           return crow::response(200, "OK");
	                                           });

	CROW_ROUTE(m_app, "/EndTurn/Return_Points")
		.methods("POST"_method)
		([this](const crow::request& req)
			{
									std::vector<std::pair<std::string, float>> pairs = m_gameHandlers.GetPlayersTurnPoints(); // Obțineți datele dorite
				

		                              const auto jsonData = crow::json::load(req.body);
		                              std::vector<crow::json::wvalue> responseJson;
									  for (const auto& [name,points] : pairs)
		                              {
										  int point = int(points);
			                              responseJson.push_back(crow::json::wvalue{{"Point", point}});
		                              }

		                              return crow::json::wvalue{responseJson};
	                              });
	//new route for end turn / return image
	//should recieve image + name from client -> std::pair<std::string, std::string>
	//CROW_ROUTE(m_app, "/EndTurn/Return_Image")
		//.methods("POST"_method)
		//([this](const crow::request& req)
			//{
				//std::vector<std::pair<std::string, std::string>> pairs = m_gameHandlers.GetPlayersTurnImage(); // Obțineți datele dorite
			
				//const auto jsonData = crow::json::load(req.body);
				//std::vector<crow::json::wvalue> responseJson;
				//for (const auto& [name, image] : pairs)
				//{
				//	responseJson.push_back(crow::json::wvalue{ {"Image", image} });
				//}

				//return crow::json::wvalue{ responseJson };
			//});

	CROW_ROUTE(m_app, "/EndGame/Return_EndGamePoints")
		.methods("POST"_method)
		([this](const crow::request& req)
			{
				std::vector<std::pair<std::string, float>> pairs = m_gameHandlers.GetPlayersGamePoints(); // Obțineți datele dorite

				

				//m_userStorage.UpdateBestScore();
				const auto jsonData = crow::json::load(req.body);
				std::vector<crow::json::wvalue> responseJson;
				for (const auto& [name, points] : pairs)
				{
					int point = int(points);
					responseJson.push_back(crow::json::wvalue{ {"Point", point} });
				}

				return crow::json::wvalue{ responseJson };
			});

	CROW_ROUTE(m_app, "/Game/Return_UsersNames")
		.methods("POST"_method)
		([this](const crow::request& req)
			{
				const auto jsonData = crow::json::load(req.body);
				std::vector<crow::json::wvalue> responseJson;
				for (const auto& name : m_usersNames)
				{
					responseJson.push_back(crow::json::wvalue{ {"name", name} });
				}

				return crow::json::wvalue{ responseJson };
			});

	m_app.port(18080).multithreaded().run();
}

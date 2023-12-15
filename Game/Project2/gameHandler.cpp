#include "gameHandler.h"
import round;
import turn;
#include <queue>


using namespace server;

GameHandler::GameHandler() {}
GameHandler::~GameHandler() {}



void GameHandler::Start()
{
	m_wordStorage.Init();
	auto nr = m_wordStorage.m_db.count<WordFromDictionary>();
	std::string s{ "eng" };
	std::queue<std::string> words = m_wordStorage.SelectWords(5, 48, s);

	m_routing.Run(m_wordStorage, m_userStorage);
	std::string currentUser = m_routing.GetLastUsername();
	m_lobby.AddPlayer(currentUser, m_userStorage.GetBestScore(currentUser), m_userStorage.GetLastMatchesPoints(currentUser));
	//Aici posibil semnal catre client ca currentuser e lobby owner si in client doar el o sa poata schimba dificultatea
	while (m_routing.GetGameStart() != true)
	{
		if (currentUser != m_routing.GetLastUsername())
		{
			m_lobby.AddPlayer(currentUser, m_userStorage.GetBestScore(currentUser), m_userStorage.GetLastMatchesPoints(currentUser)); // functiile astea 2 trb adaugate stef 
			currentUser = m_routing.GetLastUsername();
		}
		m_lobby.SetDifficulty(m_routing.GetDifficulty());
	}
	
	m_game.Start(m_lobby.GetPlayers(), m_lobby.GetDifficulty());

	m_numberOfTurns = m_lobby.GetPlayers().size();
	for (int i = 0; i <= m_game.NUMBER_OF_ROUNDS; i++)
	{
		Round round{};
		round.StartRound(m_lobby.GetPlayers(), m_game.GenerateNextWords()); //Functia asta de generate words nush exact ce face?
		for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
		{
			std::string wordToBeGuessed = words.front();
			//Trimite la server word
			round.SetRoleForEachPlayer(iterator);
			Turn turn{};
			//turn.GuessingTimeVectorInitialization(players); -> Nu stiu ce face asta????
			//BeginTurn(wordToBeGuessed);
			m_timerTurn.Reset();
			m_timerServer.Reset();
			int countDown = 60; 
			while (true && countDown != 0) {
				//Getmessages from client
				//send to client turn.VerifyInputWord(wordToBeGuessed, playerInputWord);
				// if (corect)
				//*daca e correct sa ii fie adaugat timpul in vector pe pozitia corespunzatoare
				//
				if (m_timerServer.GetElapsedTime() > 0.1)
				{
					//primeste si trimite desenul
					m_timerServer.Reset();
				}

				if (m_timerTurn.GetElapsedTime() > 1)
				{
					std::cout << countDown << "A trecut o secunda :D\n";
					countDown--;
					//sent countdown to client to update 
					m_timerTurn.Reset();
				}


			}

			/*while (exista timp || nu au ghicit toti)
				*verificare fieacre input
					*gueser daca e corect cuvantul sau daca e apropape
						*daca e correct sa ii fie adaugat timpul in vector pe pozitia corespunzatoare
				*eliminare din cenzura de la cuvant dupa x timp
				*trimitiere catre fieacare user un update
			*/




			//turn.AddPointsForEachPlayer(players);

			//wordList.pop();
			//UpdateGamePoints();
		}
	}


}
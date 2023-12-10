import user;
import round;
import utils;
import game;
import turn;
import lobby;

//#include "Timer.h"
#include "routing.h"


using namespace server;
int main()
{
	//Timer t;
	/*WordDatabaseHandle handle;
	handle.init();
	std::vector<std::string> words = handle.SelectWords(2);*/

	WordDatabaseHandle wordStorage;
	UserDatabaseHandle userStorage;

	Game game;
	Lobby lobby;
	lobby.SetDifficulty(3);

	return 80;

	/*http::Routing r;
	std::string currentUser = "";
	r.Run(wordStorage, userStorage);*/

	////Cat playerii sunt in lobby 
	//while (r.GetGameStart() != true)
	//{
	//	if (currentUser != r.GetLastUsername())
	//	{
	//		lobby.AddPlayer(currentUser, userStorage.GetBestScore(currentUser), userStorage.GetLastMatchesPoints(currentUser)); // functiile astea 2 trb adaugate stef 
	//		currentUser = r.GetLastUsername();
	//	}
	//	//lobby.SetDifficulty(r.GetDifficulty()); -> Sa modifice roby setdifficulty sa ia un int
	//}
	//Game game;
	//game.Start(lobby.GetPlayers(), lobby.GetDifficulty());
	//for (int i = 0; i <= game.NUMBER_OF_ROUNDS; i++)
	//{
	//	Round round{};
	//	round.StartRound(game.GetPlayers(), game.GenerateNextWords());

	//	for (uint8_t iterator = 0; iterator < m_numberOfTurns; iterator++)
	//	{
	//		SetRoleForEachPlayer(iterator);
	//		Turn turn{};
	//		turn.StartTurn(m_players, wordList.front());

	//		wordList.pop();
	//		UpdateGamePoints();
	//	}
	//}





}
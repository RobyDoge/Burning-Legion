import user;
import round;
import utils;
import game;
import turn;

#include "timer.h"
#include "DatabaseHandlers.h"
#include "routing.h"
import <fstream>;

using namespace server;
int main()
{
	Timer t;
	/*WordDatabaseHandle handle;
	handle.init();
	std::vector<std::string> words = handle.SelectWords(2);*/

	WordDatabaseHandle wordStorage;
	UserDatabaseHandle userStorage;
	http::Routing r;
	r.Run(wordStorage, userStorage);
	return 0;

}
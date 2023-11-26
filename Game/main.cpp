import login;
import user;
import round;
import utils;
import game;
import turn;

#include "./TimerDLL/Timer.h"
#include "DatabaseHandlers.h"

import <fstream>;

using namespace server;
int main()
{

	Turn t;
	auto a=t.Compare("M2396546854+68", "Mami");

	auto  b = t.VerifyInputWord("Tt23", "TATI");

	/*WordDatabaseHandle handle;
	handle.init();
	std::vector<std::string> words = handle.SelectWords(2);*/
	return 0;
	
}
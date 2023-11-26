import login;
import user;
import round;
import utils;
import game;

#include "./TimerDLL/Timer.h"
#include "DatabaseHandlers.h"

import <fstream>;

using namespace server;
int main()
{
	Points a, b;
	a.SetTurnPoints(23);
	b = a;

	User c, d;

	Game g;

	std::vector<std::string> x;
	std::vector<User> y;
	x.push_back("Mami");
	x.push_back("Tati");

	y.push_back(c);
	y.push_back(d);

	Round r;
	r.StartRound(y,x);

	WordDatabaseHandle handle;
	handle.init();
	std::vector<std::string> words = handle.SelectWords(2);
	return 0;
	
}
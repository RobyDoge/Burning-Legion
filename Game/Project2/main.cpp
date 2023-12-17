import user;
import round;
import utils;
import game;
import turn;
import lobby;

#include "timer.h"
#include "DatabaseHandlers.h"

import <fstream>;


#include "routing.h"
using namespace server;
int main()
{
	
	GameHandler handler{};
	Routing r{ handler };
	r.run();

	return 0;
}
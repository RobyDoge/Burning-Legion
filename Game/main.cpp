import login;
import user;
import round;
//import utils;
#include "WordDatabase.h"
import game;

#include <iostream>
//import timer;

import <fstream>;

using namespace server;
int main()
{
	//Timer timer;															 //Create an instance of the Class
	//timer.Reset();															 //Use the reset() method to set the startTime right before the Turn starts
	//int countDown = 60;														 //Set up a countDown 
	//while (true && countDown != 0)											 //Start the Turn

	//{										 

	//	if (timer.GetElapsedTime() > 1)										 //When the elapsed time hits 1 seconds
	//	{
	//		std::cout << countDown << "A trecut o secunda :D\n";
	//		countDown--;												     //Substract a second from the countDown
	//		timer.Reset();													 //Reset the timer, elapsedTime is now 0 again
	//	}
	//}


	
	Points a, b;
	a.SetTurnPoints(23);
	b = a;

	User c, d;
	c.SetPoints(a);
	d = c;

	Game g;
	return 0;
	
}
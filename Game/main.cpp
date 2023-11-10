import login;
import user;
import round;
import word;
//#include "Game.h"

#include <iostream>
#include "Timer.h"
import <fstream>;

int main()
{
	/*Timer timer;															 //Create an instance of the Class
	timer.Reset();															 //Use the reset() method to set the startTime right before the Turn starts
	int countDown = 60;														 //Set up a countDown 
	while (true && countDown != 0)											 //Start the Turn

	{										 

		if (timer.GetElapsedTime() > 1)										 //When the elapsed time hits 1 seconds
		{
			std::cout << countDown << "A trecut o secunda :D\n";
			countDown--;												     //Substract a second from the countDown
			timer.Reset();													 //Reset the timer, elapsedTime is now 0 again
		}
	}*/

	/*Game c;
	 * de testat clasa game, mie(ROBY) imi da 100+ erori can incerc sa o rulez/adaug
	 */

	game::WordList a;
	std::ifstream f("input.txt");
	f >> a;
	std::cout << a.GetRandomWord();
	return 0;
	
}
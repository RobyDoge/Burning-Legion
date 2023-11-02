import points;
import	user;
#include "Dictionary.h"
#include "Timer.h"

int main()
{
	game::Points a;
	game::User b;
	a.SetTurnPoints(1000);
	b.SetPoints(a);
	Dictionary c;

	Timer* timer = new Timer();
	bool isRunning = true;
	float countDown = 60.0f;
	timer->Reset();
	while (isRunning) {
		if (timer->GetElapsedTime() >= 1.0f) {
			std::cout << countDown<< std::endl;
			countDown--;
			timer->Reset();
		}
	}
}
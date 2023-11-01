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
	float elapsedTime = 0.0f;
	float countDown = 60.0f;
	while (isRunning) {
		timer->Tick();
		timer->Reset();
		elapsedTime += timer->GetDeltaTime();
		if (elapsedTime >= 1.0f) {
			std::cout << countDown << std::endl;
			countDown--;
			elapsedTime = 0.0f;
		}
		if (countDown == 0)
			std::cout << "stopRound()";
	}
}
export module round;
import "Game.h";
import user;
import word;
import <vector>;

using game::User;
namespace game
{
	//this class will be static because i don't want to create an object of this class
	//and i will just start the drawing and modify the points of the users
	export class Round
	{
	public:

		static void StartRound(std::vector<User>& players, const WordList& wordList);

	private:

	};
}
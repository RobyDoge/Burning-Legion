export module turn;
import round;
import user;
import <vector>;
import word;
import <string>;

namespace  game
{
	//this class will be static because i don't want a to create an object of this class
	//and i will just start the drawing and modify the points of the users
	export class Turn
	{
	public:
		static void StartTurn(std::vector<std::pair<User, uint8_t>> vectorUsers, std::string toBeDrawWord);

	private:

	};
}

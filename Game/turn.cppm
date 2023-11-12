export module turn;
import round;
import user;
import <vector>;
import <string>;

using namespace game;
namespace  game
{
	
	export class Turn
	{
	public:
		Turn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn);
		void StartTurn();

	private:
		std::vector<std::pair<User, Round::Role>> m_players;
		std::string m_wordToBeDrawn;
	};
}

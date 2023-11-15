export module round;
import user;
import <vector>;
import <string>;
import game;


namespace server
{
	//this class gets from Game a vector of the users and the words necessary for a round
	export class Round
	{
	public:
		enum class Role : uint8_t
		{
			Drawer,
			Guesser,
			Finished
		};

		Round(std::vector<User>& players, const std::vector<std::string>& wordList);
		void StartRound();

	private:
		std::vector<std::pair<User, Role>>& SetRoleForEachPlayer(const uint8_t drawerPosition) const;
		void UpdateGamePoints();



		std::vector<User> m_players;
		std::vector<std::string> m_wordList;
		uint8_t m_numberOfTurns;

	};
}
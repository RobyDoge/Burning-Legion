export module turn;
import round;
import user;
import <vector>;
import <string>;


namespace  server
{
	
	export class Turn
	{
	public:
		static constexpr uint8_t TURN_LIMIT = 60;

	public:
		void StartTurn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn);	//function to start the round



	private:
		enum class MoveDirection : bool
		{
			FromRoundToTurn,
			FromTurnToRound
		};

	private:
		void GuessingTimesInitialization();
		void Move(std::vector<std::pair<User, Round::Role>>& players, const MoveDirection moveDirection);
		void AddPointsForEachPlayer();
		void RemainingToTakenTime();
	private:
		std::vector<std::pair<User, Round::Role>> m_players;
		std::vector<std::pair<float,std::string>> m_guessingTimes;
	};
}

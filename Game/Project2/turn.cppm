export module turn;
import player;


import <vector>;
import <utility>;
import <optional>;
import <string>;
import <cstdint>;

namespace  game_logic
{

	export class Turn
	{
	public:
		static constexpr uint8_t TURN_LIMIT{ 60 };							//the duration for a turn

	public:
		enum class TurnStatus : bool	//enum for knowing if the turn is over
		{
			NotOver = false,
			Over = true
		};

	public:
		Turn() = default;
		Turn(std::vector<Player>& players, const std::string& wordToBeGuessed,const uint8_t drawerPosition);
		~Turn() = default;
		std::string VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord) const;
		void ReturnPlayers(std::vector<Player>& players);
		TurnStatus GetTurnStatus() const;
		void SwitchTurnStatus();

	private:
		enum class StringDifference : uint8_t	//used for returning how different  are two strings
		{
			NotSimilar = 0b00,					//not at all
			DifferByOneChar = 0b01,				//by one character
			DifferByTwoChars = 0b10,			//by two characters
			Identical = 0b11					//they are the same
		};
		enum class MoveDirection : bool //enum for knowing which way a move should be done
		{
			FromGameToTurn,					//the information from game are being moved to turn
			FromTurnToGame					//the information from turn are being moved to back to game
		};
		enum class Role : uint8_t	//enum defining different roles for players in a round
		{
			Drawer = 0b00,					// player drawing the word
			Guesser = 0b01,					// player guessing the word
			Finished = 0b10,				// player that guessed the word
			NoRole = 0b11					// for creating m_player at the beginning
		};
	public:
		std::vector<Player> GetPlayers();
		void AddToGuessingTimes(float timeOfGuess, const std::string& playerName);
	private:
		void GuessingTimeVectorInitialization(const uint8_t drawerPosition);		//intializes the vector for guessing times
		void AddPointsForEachPlayer(std::vector<std::pair<Player, Role>>& players);						//adds to each player their points based on the guessing time
		void ConvertRemainingTimeToTakenTime();							//converts the remaining time stored in guessingTimes to how much it tool everyone to guess
		void Move(std::vector<Player>& players, const MoveDirection moveDirection);
		StringDifference Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord) const;

	private:
		std::vector<std::pair<Player, Role>> m_players{};			//stores the players and their roles
		std::vector<std::pair<float, std::string>> m_guessingTimes{};		//stores the time taken for guessing
		TurnStatus m_turnStatus{ TurnStatus::NotOver };				//stores if the turn is over
	};
}

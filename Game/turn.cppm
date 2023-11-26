export module turn;
import round;
import user;
import <vector>;
import <string>;
import <optional>;

namespace  server
{
	
	export class Turn
	{
	public:
		static constexpr uint8_t TURN_LIMIT = 60;							//the duration for a turn

	public:
		void StartTurn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn);	//function to start the round



	private:			
		enum class MoveDirection : bool					//enum for knowing which way a move should be done
		{
			FromRoundToTurn,					//the information received from round are being moved to turn
			FromTurnToRound						//the information from turn are being moved to back to round
		};
		enum class StringDifference : uint8_t			//used for returning how different  are two strings
		{
			NotSimilar = 0b00,					//not at all
			DifferByOneChar = 0b01,				//by one character
			DifferByTwoChars = 0b10,			//by two characters
			Identical = 0b11					//they are the same
		};

	private:
		void GuessingTimesInitialization();						//intializes the vector for guessing times
		void Move(std::vector<std::pair<User, Round::Role>>& players, const MoveDirection moveDirection);		//does the move of elements
		void AddPointsForEachPlayer();							//adds to each player their points based on the guessing time
		void RemainingToTakenTime();							//converts the remaining time stored in guessingTime to how much it tool everyone to guess
		//void BeginTurn();										//begins the turn
	public:
		//compare the two strings and based on how may characters are different returns a StringDifference
		StringDifference Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord);
		//based on the two input string returns a pair of a message to be written for everyone in chat and an optional message written only for player responsible for the second string
		std::pair<std::string, std::optional<std::string>> VerifyInputWord(const std::string& wordToBeDrawn, const std::string& playerInputWord);

	private:
		std::vector<std::pair<User, Round::Role>> m_players;			//stores the players
		std::vector<std::pair<float,std::string>> m_guessingTimes;		//stores the time taken for guessing
	};
}

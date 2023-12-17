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
		static constexpr uint8_t TURN_LIMIT = 60;							//the duration for a turn

	public:
		Turn() = default;
		~Turn() = default;
		void StartTurn(std::vector<std::pair<Player, Round::Role>>& players, const std::string& wordToBeDrawn);	//function to start the round
		std::pair<std::string, std::optional<std::string>> VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord) const;


	private:
		enum class StringDifference : uint8_t			//used for returning how different  are two strings
		{
			NotSimilar = 0b00,					//not at all
			DifferByOneChar = 0b01,				//by one character
			DifferByTwoChars = 0b10,			//by two characters
			Identical = 0b11					//they are the same
		};

	private:
		void GuessingTimeVectorInitialization(const std::vector<std::pair<Player, Round::Role>>& players);		//intializes the vector for guessing times
		void AddPointsForEachPlayer(std::vector<std::pair<Player, Round::Role>>& players);						//adds to each player their points based on the guessing time
		void ConvertRemainingTimeToTakenTime();							//converts the remaining time stored in guessingTimes to how much it tool everyone to guess
		//void BeginTurn(const std::string& wordToBeGuessed);			//begins the turn

		//compare the two strings and based on how may characters are different returns a StringDifference
		StringDifference Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord) const;
		//returns {message to be written in chat, optional message to be displayed only to the player that gave the input}

	private:
		std::vector<std::pair<float, std::string>> m_guessingTimes{};		//stores the time taken for guessing
	};
}

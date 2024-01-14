export module turn;
import player;

import <vector>;
import <utility>;
import <optional>;
import <string>;
import <cstdint>;
import <unordered_map>;

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
		~Turn() = default;
		Turn(std::vector<Player>& players, const std::string& drawerName);

		TurnStatus GetTurnStatus() const;
		std::vector<Player> GetPlayers() const;

		void SwitchTurnStatus();
		static std::string VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord);
		void ReturnPlayers(std::vector<Player>& players);
		std::vector<std::pair<std::string, uint16_t>> AddPointsForEachPlayer();						//adds to each player their points based on the guessing time
		void AddToGuessingTimes(float timeOfGuess, const std::string& playerName);
		void FillGuessingTimes();

	private:
		enum class StringDifference : uint8_t	//used for returning how different  are two strings
		{
			NotSimilar = 0b00,					//not at all
			DifferByOneChar = 0b01,				//by one character
			DifferByTwoChars = 0b10,			//by two characters
			Identical = 0b11					//they are the same
		};

	private:
		std::vector<std::pair<std::string, uint16_t>> Players_TurnPoints();
		std::vector<float> OnlyGuessingTimes();
		void ConvertRemainingTimeToTakenTime();							//converts the remaining time stored in guessingTimes to how much it tool everyone to guess
		static StringDifference Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord);

	private:
		std::vector<Player> m_players{};		//stores the players
		std::unordered_map<std::string,std::optional<float>> m_guessingTimes{};	//stores the time taken for guessing
		TurnStatus m_turnStatus{ TurnStatus::NotOver };				//stores if the turn is over
	};
}

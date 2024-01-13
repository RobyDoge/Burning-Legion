module turn;
import player;
import game;

import <vector>;
import <string>;
import <utility>;
import <optional>;
import <algorithm>;
import <string>;
import <ranges>;



using namespace game_logic;

Turn::Turn(std::vector<Player>& players)
{
	Move(players, MoveDirection::FromGameToTurn);

}

void Turn::ReturnPlayers(std::vector<Player>& players)
{
	Move(players, MoveDirection::FromTurnToGame);
}

void Turn::Move(std::vector<Player>& players, const MoveDirection moveDirection)
{
	if (moveDirection == MoveDirection::FromGameToTurn)
	{
		m_players.clear();
		m_players.resize(players.size());
		std::ranges::transform(players, m_players.begin(),
		                       [](Player& user)
		                       {
			                       return std::make_pair<Player, Role>(std::move(user), Role::NoRole);
		                       }
		);
		players.clear();
		return;
	}

	players.resize(m_players.size());
	std::ranges::transform(m_players,players.begin(),
			[](const std::pair<Player&, Role> pair)
			{
				return std::move(pair.first);
			}
	);
}


std::vector<Player> Turn::GetPlayers()
{
		std::vector<Player> players;
		players.reserve(m_players.size()); 

		std::ranges::transform(m_players, std::back_inserter(players),
		                       [](const std::pair<Player, Role>& pair) {
			                       return pair.first;
		                       });

		return players;
}

void Turn::AddToGuessingTimes(const float timeOfGuess, const std::string& playerName)
{
	m_guessingTimes[playerName] = timeOfGuess;
}

std::vector<float> Turn::OnlyGuessingTimes()
{
	std::vector<float> guessingTimes;
	std::ranges::for_each(m_guessingTimes, [&guessingTimes](const auto& PlayerName_GuessingTime)
	{
		if (PlayerName_GuessingTime.second.has_value())
			guessingTimes.push_back(PlayerName_GuessingTime.second.value());
	});
	return guessingTimes;
}


std::string Turn::VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord)
{
	switch (Compare(wordToBeGuessed, playerInputWord))
	{
	case StringDifference::Identical:
		return "Correct Guess";
	case StringDifference::DifferByOneChar:
		return "Very Close";
	case StringDifference::DifferByTwoChars:
		return "Close";
	default:
		return playerInputWord;
	}
}

Turn::TurnStatus Turn::GetTurnStatus() const
{
	return m_turnStatus;
}


void Turn::SwitchTurnStatus()
{
	m_turnStatus = static_cast<TurnStatus>(!static_cast<bool>(m_turnStatus));
}


Turn::StringDifference Turn::Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord)
{
	if (wordToBeDrawn.length() != playerInputWord.length())
		return StringDifference::NotSimilar;

	auto positionIteratorOfMismatch =
		std::mismatch(wordToBeDrawn.begin(),
			wordToBeDrawn.end(),
			playerInputWord.begin());
	if (positionIteratorOfMismatch.first == wordToBeDrawn.end())
		return StringDifference::Identical;

	int positionOfMismatch = positionIteratorOfMismatch.first - wordToBeDrawn.begin();
	positionIteratorOfMismatch = std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
		wordToBeDrawn.end(),
		playerInputWord.begin() + positionOfMismatch + 1);
	if (positionIteratorOfMismatch.first == wordToBeDrawn.end())
		return StringDifference::DifferByOneChar;

	positionOfMismatch = positionIteratorOfMismatch.first - wordToBeDrawn.begin();
	positionIteratorOfMismatch = std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
		wordToBeDrawn.end(),
		playerInputWord.begin() + positionOfMismatch + 1);
	if (positionIteratorOfMismatch.first == wordToBeDrawn.end())
		return StringDifference::DifferByTwoChars;

	return StringDifference::NotSimilar;
}



void Turn::AddPointsForEachPlayer(std::vector<std::pair<Player, Role>>& players)
{
	ConvertRemainingTimeToTakenTime();
	for (auto& [playerName,playerRole]: players)
	{
		if(playerRole==Role::Drawer)
		{

			playerName.ChangePoints().AddToTurnPoints(OnlyGuessingTimes());
			continue;
		}
		playerName.ChangePoints().AddToTurnPoints(m_guessingTimes.at(playerName.GetName()).value());
	}
}

void Turn::ConvertRemainingTimeToTakenTime()
{
	for (auto& remainingTime : m_guessingTimes | std::views::values)
	{
		if(remainingTime.has_value())
			remainingTime = -remainingTime.value() + TURN_LIMIT;
	}
}

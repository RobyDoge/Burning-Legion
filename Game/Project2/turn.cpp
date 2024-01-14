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

Turn::Turn(std::vector<Player>& players, const std::string& drawerName)
{
	std::ranges::move(players, std::back_inserter(m_players));
	m_guessingTimes[drawerName] = std::nullopt;

}

void Turn::ReturnPlayers(std::vector<Player>& players)
{
	std::ranges::move(m_players, std::back_inserter(players));
}

std::vector<Player> Turn::GetPlayers() const
{
	return m_players;
}

void Turn::AddToGuessingTimes(const float timeOfGuess, const std::string& playerName)
{
	m_guessingTimes[playerName] = timeOfGuess;
}

void Turn::FillGuessingTimes()
{
	for (auto& player : m_players)
	{
		if (!m_guessingTimes.contains(player.GetName()))
			m_guessingTimes[player.GetName()] = 0.0f;
	}
}

std::vector<std::pair<std::string, int16_t>> Turn::Players_TurnPoints()
{
	std::vector<std::pair<std::string, int16_t>> players_turnPoints;
	std::ranges::transform(m_players, std::back_inserter(players_turnPoints),
	                       [](const Player& player)
	                       {
		                       return std::make_pair(player.GetName(), player.GetPoints().GetTurnPoints());
	                       });
	return players_turnPoints;
}

std::vector<float> Turn::OnlyGuessingTimes()
{
	std::vector<float> guessingTimes;
	std::ranges::for_each(m_guessingTimes, [&guessingTimes](const auto& playerName_guessingTime)
		{
			if (playerName_guessingTime.second.has_value())
				guessingTimes.push_back(playerName_guessingTime.second.value());
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

std::vector<std::pair<std::string, int16_t>> Turn::AddPointsForEachPlayer()
{
	ConvertRemainingTimeToTakenTime();
	for (auto& player: m_players)
	{
		if(!m_guessingTimes.at(player.GetName()).has_value())
		{

			player.ChangePoints().AddToTurnPoints(OnlyGuessingTimes());
			continue;
		}
		player.ChangePoints().AddToTurnPoints(m_guessingTimes.at(player.GetName()).value());
	}
	return Players_TurnPoints();
}

void Turn::ConvertRemainingTimeToTakenTime()
{
	for (auto& remainingTime : m_guessingTimes | std::views::values)
	{
		if(remainingTime.has_value())
			remainingTime = -remainingTime.value() + TURN_LIMIT;
	}
}

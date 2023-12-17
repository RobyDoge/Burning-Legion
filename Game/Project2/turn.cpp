module turn;
import player;
import game;

//routing

import <vector>;
import <string>;
import <utility>;
import <optional>;
import <algorithm>;
import <string>;
import <ranges>;

//#include "TimerDLL/Timer.h"

using namespace game_logic;

Turn::Turn(std::vector<Player>& players, const std::string& wordToBeDrawn, const uint8_t drawerPosition)
{
	Move(players, MoveDirection::FromGameToTurn);
	GuessingTimeVectorInitialization(drawerPosition);

}

void Turn::Move(std::vector<Player>& players, const MoveDirection moveDirection)
{
	if (moveDirection == MoveDirection::FromGameToTurn)
	{
		m_players.clear();
		m_players.resize(players.size());
		std::transform(
			players.begin(),
			players.end(),
			m_players.begin(),
			[](Player& user)
		{
			return std::make_pair<Player, Role>(std::move(user), Role::NoRole);
		}
		);
		players.clear();
		return;
	}
	players.resize(m_players.size());
	std::transform(
		m_players.begin(),
		m_players.end(),
		players.begin(),
		[](const std::pair<Player&, Role> pair)
	{
		return std::move(pair.first);
	}
	);
}


void Turn::GuessingTimeVectorInitialization(const uint8_t drawerPosition)
{
	m_guessingTimes.resize(m_players.size());
	for (uint8_t iterator = 0; iterator < m_players.size(); iterator++)
	{
		if (iterator==drawerPosition)
		{
			m_guessingTimes[iterator].first = -2;
			continue;
		}
		m_guessingTimes[iterator].first = -1;
	}
}

std::pair<std::string, std::optional<std::string>> Turn::VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord) const
{
	switch (Compare(wordToBeGuessed, playerInputWord))
	{
	case StringDifference::Identical:
		return { "guessed correctly!", std::nullopt };
	case StringDifference::DifferByOneChar:
		return { playerInputWord, "YOU ARE SO CLOSE" };
	case StringDifference::DifferByTwoChars:
		return { playerInputWord, "YOU ARE CLOSE" };
	default:
		return { playerInputWord, std::nullopt };
	}

	return {};
}


Turn::StringDifference Turn::Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord) const
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



void Turn::AddPointsForEachPlayer(std::vector<std::pair<Player, Round::Role>>& players)
{
	ConvertRemainingTimeToTakenTime();
	for (uint8_t iterator = 0; iterator < players.size(); iterator++)
	{
		if (players[iterator].second != Round::Role::Drawer)
		{
			players[iterator].first.GetPoints().SetTurnPoints(m_guessingTimes[iterator].first);
			continue;
		}
		std::vector<float> floatVector;
		for (uint8_t iterator2 = 0; iterator2 < m_guessingTimes.size(); iterator2++)
		{
			if (iterator == iterator2)
			{
				continue;
			}
			floatVector.push_back(m_guessingTimes[iterator2].first);
		}
		players[iterator].first.GetPoints().SetTurnPoints(floatVector);
	}
}

void Turn::ConvertRemainingTimeToTakenTime()
{
	for (auto& remainingTime : m_guessingTimes | std::views::keys)
	{
		remainingTime = TURN_LIMIT - remainingTime;
	}
}

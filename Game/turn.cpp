module turn;
import user;
import round;
import <string>;
import <vector>;
import <algorithm>;
import <optional>;

#include "TimerDLL/Timer.h"

using server::Turn;
using namespace server;


void Turn::StartTurn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn)
{
	Move(players, MoveDirection::FromRoundToTurn);
	GuessingTimesInitialization();
	//BeginTurn();
	

	/*while (exista timp || nu au ghicit toti)
		*verificare fieacre input
			*gueser daca e corect cuvantul sau daca e apropape
				*daca e correct sa ii fie adaugat timpul in vector pe pozitia corespunzatoare
				*revocare drept de scriere
		*eliminare din cenzura de la cuvant dupa x timp
		*trimitiere catre fieacare user un update
	*/

	


	AddPointsForEachPlayer();
	Move(players, MoveDirection::FromTurnToRound);
}

//necesita cunostinte pe care inca nu le am (ROBY) dar se vor dobandii in cel mai scurt timp
//void Turn::BeginTurn()
//{
//	Timer timer;
//	uint16_t remainingTicks = TURN_LIMIT*100;
//	uint8_t numberOfFinishedPlayers = 0;
//
//	timer.Reset();
//	while (remainingTicks != 0 && numberOfFinishedPlayers != m_players.size() - 1) 
//	{
//		if (timer.GetElapsedTime() > 0.01)
//		{
//			remainingTicks--;
//			timer.Reset();
//		}
//	}
//}

std::pair < std::string, std::optional<std::string>> Turn::VerifyInputWord(const std::string& wordToBeDrawn, const std::string& playerInputWord) const
{
	const auto difference = Compare(wordToBeDrawn, playerInputWord);

	switch(difference)
	{
	case StringDifference::Identical:
		return { "guessed correctly!",std::nullopt };
	case StringDifference::NotSimilar:
		return { playerInputWord,std::nullopt };
	case StringDifference::DifferByOneChar:
		return{ playerInputWord,"YOU ARE SO CLOSE" };
	case StringDifference::DifferByTwoChars:
		return { playerInputWord,"YOU ARE CLOSE" };
	}
}

Turn::StringDifference Turn::Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord) const
{
	if (wordToBeDrawn.size() != playerInputWord.size())
		return StringDifference::NotSimilar;

	auto mismatch = std::mismatch(wordToBeDrawn.begin(),
	                                   wordToBeDrawn.end(),
	                                   playerInputWord.begin());
	if (mismatch.first == wordToBeDrawn.end())
		return StringDifference::Identical;

	int positionOfMismatch = mismatch.first - wordToBeDrawn.begin();
	mismatch = std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
	                                    wordToBeDrawn.end(),
	                                    playerInputWord.begin() + positionOfMismatch + 1);
	if (mismatch.first == wordToBeDrawn.end())
		return StringDifference::DifferByOneChar;

	positionOfMismatch = mismatch.first - wordToBeDrawn.begin() ;
	mismatch=std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
										wordToBeDrawn.end(),
										playerInputWord.begin() + positionOfMismatch + 1);
	if (mismatch.first == wordToBeDrawn.end())
		return StringDifference::DifferByTwoChars;

	return StringDifference::NotSimilar;
}

void Turn::Move(std::vector<std::pair<User, Round::Role>>& players, const MoveDirection moveDirection)
{
	if (moveDirection == MoveDirection::FromRoundToTurn)
	{
		m_players = std::move(players);
		return;
	}
	players = std::move(m_players);
}

void Turn::GuessingTimesInitialization()
{
	m_guessingTimes.resize(m_players.size());
	for(uint8_t iterator = 0; iterator < m_players.size(); iterator++)
	{
		m_guessingTimes[iterator].second = m_players[iterator].first.GetName();
		if (m_players[iterator].second == Round::Role::Drawer)
		{
			m_guessingTimes[iterator].first = -2;
			continue;
		}
		m_guessingTimes[iterator].first = -1;
	}
}


void Turn::AddPointsForEachPlayer()
{
	RemainingToTakenTime();
	for (uint8_t iterator = 0; iterator < m_players.size(); iterator++)
	{
		if (m_players[iterator].second == Round::Role::Drawer)
		{
			std::vector<float> floatVector;
			for(uint8_t iterator2 = 0; iterator2 < m_guessingTimes.size(); iterator2++)
			{
				if(iterator==iterator2)
				{
					continue;
				}
				floatVector.push_back(m_guessingTimes[iterator2].first);
			}
			m_players[iterator].first.GetPoints().SetTurnPoints(floatVector);
			continue;
		}
		m_players[iterator].first.GetPoints().SetTurnPoints(m_guessingTimes[iterator].first);
	}
}

void Turn::RemainingToTakenTime()
{
	for(auto& guessTime:m_guessingTimes)
	{
		guessTime.first = TURN_LIMIT - guessTime.first;
	}
}

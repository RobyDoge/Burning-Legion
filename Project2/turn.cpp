module turn;
import user;
import round;
import <vector>;

//#include "TimerDLL/Timer.h"

using namespace server;

void Turn::StartTurn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeGuessed)
{
	GuessingTimeVectorInitialization(players);
	//BeginTurn(wordToBeGuessed);


	/*while (exista timp || nu au ghicit toti)
		*verificare fieacre input
			*gueser daca e corect cuvantul sau daca e apropape
				*daca e correct sa ii fie adaugat timpul in vector pe pozitia corespunzatoare
				*revocare drept de scriere
		*eliminare din cenzura de la cuvant dupa x timp
		*trimitiere catre fieacare user un update
	*/




	AddPointsForEachPlayer(players);
}


void Turn::GuessingTimeVectorInitialization(const std::vector<std::pair<User, Round::Role>>& players)
{
	m_guessingTimes.resize(players.size());
	for (uint8_t iterator = 0; iterator < players.size(); iterator++)
	{
		m_guessingTimes[iterator].second = players[iterator].first.GetName();
		if (players[iterator].second == Round::Role::Drawer)
		{
			m_guessingTimes[iterator].first = -2;
			continue;
		}
		m_guessingTimes[iterator].first = -1;
	}
}

//necesita cunostinte pe care inca nu le am (ROBY), dar se vor dobandii in cel mai scurt timp
//void Turn::BeginTurn(const std::string& wordToBeGuessed)
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

std::pair<std::string, std::optional<std::string>> Turn::VerifyInputWord(const std::string& wordToBeGuessed, const std::string& playerInputWord) const
{
	switch (const auto difference = Compare(wordToBeGuessed, playerInputWord))
	{
	case StringDifference::Identical:
		return { "guessed correctly!", std::nullopt };
	case StringDifference::NotSimilar:
		return { playerInputWord, std::nullopt };
	case StringDifference::DifferByOneChar:
		return { playerInputWord, "YOU ARE SO CLOSE" };
	case StringDifference::DifferByTwoChars:
		return { playerInputWord, "YOU ARE CLOSE" };
	}
}


Turn::StringDifference Turn::Compare(const std::string& wordToBeDrawn, const std::string& playerInputWord) const
{
	if (wordToBeDrawn.size() != playerInputWord.size())
		return StringDifference::NotSimilar;

	auto mismatch =
		std::mismatch(wordToBeDrawn.begin(),
			wordToBeDrawn.end(),
			playerInputWord.begin());
	if (mismatch.first == wordToBeDrawn.end())
		return StringDifference::Identical;

	int positionOfMismatch = mismatch.first - wordToBeDrawn.begin();
	auto mismatch1 = std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
		wordToBeDrawn.end(),
		playerInputWord.begin() + positionOfMismatch + 1);
	if (mismatch1.first == wordToBeDrawn.end())
		return StringDifference::DifferByOneChar;

	positionOfMismatch = mismatch.first - wordToBeDrawn.begin();
	auto mismatch2 = std::mismatch(wordToBeDrawn.begin() + positionOfMismatch + 1,
		wordToBeDrawn.end(),
		playerInputWord.begin() + positionOfMismatch + 1);
	if (mismatch2.first == wordToBeDrawn.end())
		return StringDifference::DifferByTwoChars;

	return StringDifference::NotSimilar;
}



void Turn::AddPointsForEachPlayer(std::vector<std::pair<User, Round::Role>>& players)
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
	/*for (auto& remainingTime : m_guessingTimes | std::views::keys)
	{
		remainingTime = TURN_LIMIT - remainingTime;
	}*/
}

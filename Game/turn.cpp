module turn;
import user;
import round;
import <string>;
import <vector>;
import <algorithm>;

namespace server
{
	class User;
}

using server::Turn;
using namespace server;



void Turn::StartTurn(std::vector<std::pair<User, Round::Role>>& players, const std::string& wordToBeDrawn)
{
	Move(players, MoveDirection::FromRoundToTurn);
	GuessingTimesInitialization();
	
	/*while (exista timp || nu au ghicit toti)
		*verificare fieacre input
			*gueser daca e corect cuvantul sau daca e apropape
				*daca e correct sa ii fie adaugat timpul in vector pe pozitia corespunzatoare
				*revocare drept de scriere
		*eliminare din cenzura de la cuvant dupa x timp
		*trimitiere catre fieacare user un update
	*/
	if (m_players[0].second == Round::Role::Drawer)
		m_guessingTimes[1].first = 58;
	else
		m_guessingTimes[0].first = 0;

	AddPointsForEachPlayer();
	Move(players, MoveDirection::FromTurnToRound);
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

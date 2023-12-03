module game;
import user;
import round;

import <cstdint>;
//import std;


using namespace server;

Game::Game(Lobby& lobby)
{
	m_players = lobby.GetPlayers();
	m_difficulty = lobby.GetDifficulty();
}

std::queue<std::string>& Game::GenerateNextWords()
{
	std::queue<std::string> wordsForRound{};
	for(int i =0;i< m_numberOfPlayers;i++)
	{
		wordsForRound.push(m_currentWordList.front());
		m_currentWordList.pop();
	}
	return wordsForRound;
}

void Game::CreateWordsForGame()
{
	//m_currentWordList = WordDatabaseHandle::SelectWords(m_numberOfPlayers * NUMBER_OF_ROUNDS, m_difficulty);
}

//void Game::Start(std::vector<User>& players, const Lobby::GameDifficulty difficulty)
//{
//	m_difficulty = difficulty;
//	m_numberOfPlayers = players.size();
//	CreateWordsForGame();
//
//	for(int i = 0;i<= NUMBER_OF_ROUNDS;i++)
//	{
//		Round round;
//		round.StartRound(players, GenerateNextWords());
//	}
//	UpdateLastMatches(players);
//	auto topThreePlayers{ FindTheThreeWinners(players) };
//	//signal for showing the winners;
//}

void Game::UpdateLastMatches(std::vector<User>& players)
{
	for(auto& player : players)
	{
		player.GetPoints().AddMatch();
	}
}

std::array<std::optional<User>, 3> Game::FindTheThreeWinners(std::vector<User>& players)
{

	if (players.size() == 1)
	{
		return { players[0], std::nullopt, std::nullopt };
	}
	if (players.size() == 2)
	{
		std::array<User, 2> winners{};
		if (players[0].GetPoints().GetLastMatchesPoints().front() > players[1].GetPoints().GetLastMatchesPoints().front())
		{
			winners[0] = players[0];
			winners[1] = players[1];
		}
		else
		{
			winners[0] = players[1];
			winners[1] = players[0];
		}
		return { winners[0],winners[1],std::nullopt };
	}
	auto playerCopy{players};
	std::partial_sort(playerCopy.begin(), playerCopy.begin() + 3, playerCopy.end(), [](User& first,User& second)
	{
		return first.GetPoints().GetLastMatchesPoints().front() > second.GetPoints().GetLastMatchesPoints().front();
	});
	return { playerCopy[0],playerCopy[1],playerCopy[2] };

}

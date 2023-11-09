#pragma once
import <unordered_set>;
import <cstdint>;
import <vector>;
import user; 
import word;

using game::WordList;
using game::User;

class Game
{	
public:
	Game() = default;														//default constructor
	~Game() = default;														//destructor

	void AddPlayer(const User& newPlayer);									//adds players to m_player
	void GenerateCurrentWordList(WordList& baseWordList);					//generates the words needed for the game from the word list

private:
	WordList m_currentWordList;												//the needed words for the game
	static constexpr uint8_t ROUND = 4;										//the number of rounds
	std::vector <User> m_players;											//vector storing players
};


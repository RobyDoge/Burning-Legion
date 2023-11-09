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
	Game() = default;
	~Game() = default;

	void AddPlayer(const User& newPlayer);
	void GenerateCurrentWordList(WordList& baseWordList);

private:
	WordList m_currentWordList;
	static constexpr uint8_t ROUND = 4;
	std::vector <User> m_players;
};


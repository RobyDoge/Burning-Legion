#pragma once
import <unordered_set>;
import word;
import <cstdint>;
using game::WordList;
import <vector>;

class Game
{	
public:
	Game() = default;
	~Game() = default;

	void AddPlayer();
	void generateCurrentWordList(WordList& baseWordList);

private:
	WordList m_currentWordList;
	uint8_t m_players;
	static constexpr uint8_t TURNS = 4;
};


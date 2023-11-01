#pragma once
#include<string>
#include<vector>
#include <fstream>
//#include <ranges>
#include <algorithm>

class Word
{
public:
	Word();
	~Word();
	Word(const Word& word);

	std::string GetWord() const;
	std::vector<std::string> GetLexicalFamily() const;
	void SetWord(const std::string& word);
	void SetLexicalFamily(const std::vector<std::string>& lexicalFamily);

	bool IsInLexicalFamily(const std::string& wordToFind) const;
	friend std::istream& operator >>(std::istream& wordFile, Word& word);

private:
	std::string m_word;									//the given to be guessed
	std::vector<std::string> m_lexicalFamily;			//its lexical family
};


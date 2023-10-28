#pragma once
#include<string>
#include<vector>
class Word
{
public:
	Word();
	~Word();
	Word(const Word& word);
	std::string getWord() const;
	std::vector<std::string> getLexicalFamily() const;
private:
	std::string m_word;
	std::vector<std::string> m_lexicalFamily;
};


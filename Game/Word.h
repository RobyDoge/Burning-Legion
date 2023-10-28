#pragma once
#include<string>
class Word
{
public:
	Word();
	~Word();
	Word(const Word& word);
	std::string getWord();
	std::string getLexicalFamily();
private:
	std::string m_word;
	std::string m_lexicalFamily;
};


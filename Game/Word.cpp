#include "Word.h"

Word::Word()
{
	m_word = "";
}

Word::~Word()
{
}

Word::Word(const Word& word)
{
	m_word = word.m_word;
	m_lexicalFamily = word.m_lexicalFamily;
}

std::string Word::getWord() const
{
	return m_word;
}

std::vector<std::string> Word::getLexicalFamily() const
{
	return m_lexicalFamily;
}


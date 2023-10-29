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

void Word::setWord(const std::string& word)
{
	m_word = word;
}

void Word::setLexicalFamily(const std::vector<std::string>& lexicalFamily)
{
	m_lexicalFamily = lexicalFamily;
}

bool Word::SeachWordInLexicalFamily(const std::string& wordToFind) const
{
	for (const std::string& lexicalWord : m_lexicalFamily)
		if (lexicalWord == wordToFind)
			return true;
	return false;
}

std::istream& operator>>(std::istream& wordFile, Word& word) 
{
    std::string newWord;
    std::vector<std::string> lexicalFamily;
    if (wordFile >> newWord)
    {
        std::string wordFromFamily;
        while (wordFile >> wordFromFamily)
            lexicalFamily.push_back(wordFromFamily);

        word.setWord(newWord);
        word.setLexicalFamily(lexicalFamily);
    }
    return wordFile;
}

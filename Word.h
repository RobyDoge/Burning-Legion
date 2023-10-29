#pragma once
#include<string>
#include<vector>
#include <fstream>

class Word
{
public:
	Word();
	~Word();
	Word(const Word& word);
	std::string getWord() const;
	std::vector<std::string> getLexicalFamily() const;
	void setWord(const std::string& word);
	void setLexicalFamily(const std::vector<std::string>& lexicalFamily);
	bool SeachWordInLexicalFamily(const std::string& wordToFind) const;
	friend std::istream& operator >>(std::istream& wordFile, Word& word);

private:
	std::string m_word;
	std::vector<std::string> m_lexicalFamily;
};


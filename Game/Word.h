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
	void setWord(const std::string& word);
	void setLexicalFamily(const std::vector<std::string>& lexicalFamily);
	bool SeachWordInLexicalFamily(const std::string& wordToFind) const;
private:
	std::string m_word;
	std::vector<std::string> m_lexicalFamily;
};


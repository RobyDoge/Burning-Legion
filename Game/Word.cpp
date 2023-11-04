import word;
using game::Word;



Word::Word()
{
    m_word = "";
}

Word::~Word() = default;

Word::Word(const Word& word)
{
    m_word = word.m_word;
    m_lexicalFamily = word.m_lexicalFamily;
}

std::string Word::GetWord() const
{
    return m_word;
}

std::vector<std::string> Word::GetLexicalFamily() const
{
    return m_lexicalFamily;
}

void Word::SetWord(const std::string& word)
{
    m_word = word;
}

void Word::SetLexicalFamily(const std::vector<std::string>& lexicalFamily)
{
    m_lexicalFamily = lexicalFamily;
}

bool Word::IsInLexicalFamily(const std::string& wordToFind) const
{
    return std::ranges::any_of(m_lexicalFamily,
        [&wordToFind](const std::string& lexicalWord)
        {
            return lexicalWord == wordToFind;
        });
}

std::istream& game::operator>>(std::istream& wordFile, Word& word)
{
    std::string newWord;
    std::vector<std::string> lexicalFamily;
    if (wordFile >> newWord)
    {
        std::string wordFromFamily;
        while (wordFile >> wordFromFamily)
            lexicalFamily.push_back(wordFromFamily);

        word.SetWord(newWord);
        word.SetLexicalFamily(lexicalFamily);
    }
    return wordFile;
}

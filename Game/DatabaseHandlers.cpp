import lobby;

#include"DatabaseHandlers.h"
#include<fstream>
#include<iostream>
#include<vector>

void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::vector<WordFromDictionary> words;
    uint16_t idCounter = 1;

    std::string word;
    uint8_t difficulty;
    while (inputFile >> word >> difficulty)
    {
        words.emplace_back(WordFromDictionary{ idCounter++, word, difficulty });
    }

    dictionary.insert_range(words.begin(), words.end());
}

void AddNewUser(UserDatabase& users, const std::string name, const std::string& password)
{
    uint16_t idCounter = 1;
    users.insert(UserInfo{ idCounter++, name, password, "0", 0 });
}

void WordDatabaseHandle::Init()
{
    time_t lastModifiedTime = 1700958134;            //will fix this magic number
    if (hasFileChanged("input.txt", lastModifiedTime))
        m_db.remove_all<WordFromDictionary>();
    m_db.sync_schema();
    auto initalwordscount = m_db.count<WordFromDictionary>();
    if (initalwordscount == 0)
        PopulateDictionaryFromFile(m_db, "input.txt");

    auto initalwordscount2 = m_db.count<WordFromDictionary>();
    std::cout << initalwordscount2;
}

std::queue<std::string> WordDatabaseHandle::SelectWords(const uint8_t numberOfPlayers, const server::Lobby::GameDifficulty difficulty)
{
    std::queue<std::string> generatedWords;
    uint8_t wordsNeeded = 4 * numberOfPlayers;
    //auto initalwordscount = db.count<WordFromDictionary>();
    auto rows = m_db.select(sqlite_orm::columns(&WordFromDictionary::word),
        sqlite_orm::where(sqlite_orm::c(&WordFromDictionary::difficulty) == static_cast<unsigned char>(difficulty)),
        sqlite_orm::limit(wordsNeeded));


    for (const auto& row : rows)                // Add words from the database to the vector
    {
        generatedWords.push(std::get<0>(row));
    }
    return generatedWords;
}

void WordDatabaseHandle::ClearDictionary()
{
    m_db.remove_all<WordFromDictionary>();
}

void UserDatabaseHandle::AddUser(const std::string& name, const std::string& password)
{
    m_db.sync_schema();
    AddNewUser(m_db, name, password);
}

bool UserDatabaseHandle::Authenticate(const std::string &name, const std::string& password)
{
    auto rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
        sqlite_orm::where(
            sqlite_orm::and_(
                sqlite_orm::c(&UserInfo::name) == name,
                sqlite_orm::c(&UserInfo::password) == password
            )));
    if(rows.empty())
    {
        rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
            sqlite_orm::where
            (sqlite_orm::c(&UserInfo::name) == name)
        );
	    if(rows.empty())
	    {
            //user ul exista dar nu a pus bine parola
            return false;
	    }
        //user ul nu exista
        return false;
    }
    return true;//username ul si parola exista
}

bool UserDatabaseHandle::CheckUsername(const std::string& name)
{
    //Check if userName already exists in the database

    auto rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
        sqlite_orm::where
        (sqlite_orm::c(&UserInfo::name) == name)
    );
    if(rows.empty())
    {
	    //user ul nu exista, username disponibil
        return false;
    }
    return true; //numele exista deja
}
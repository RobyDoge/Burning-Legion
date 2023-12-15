#include"DatabaseHandlers.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<list>

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
    std::string language;
    uint8_t difficulty;

    inputFile >> language;
    while (inputFile >> word >> difficulty)
    {
        if (word.compare(language) && difficulty == '3')
            inputFile >> language >> word >> difficulty;
        words.emplace_back(WordFromDictionary{ idCounter++, word, difficulty ,language});
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
    //time_t lastModifiedTime = 1702233024;            //will fix this magic number
    //if (hasFileChanged("input.txt", lastModifiedTime))
        m_db.remove_all<WordFromDictionary>();
    m_db.sync_schema();

    auto initalwordscount = m_db.count<WordFromDictionary>();
    if (initalwordscount == 0)
        PopulateDictionaryFromFile(m_db, "input.txt");

    auto initalwordscount2 = m_db.count<WordFromDictionary>();
    std::cout << initalwordscount2;
}

std::queue<std::string> WordDatabaseHandle::SelectWords(uint8_t wordsNeeded, uint8_t difficulty, std::string language)//server::Lobby::GameDifficulty difficulty
{
    std::queue<std::string> generatedWords;
    auto rows = m_db.select(sqlite_orm::columns(&WordFromDictionary::word),
        sqlite_orm::where(
            sqlite_orm::and_(
                sqlite_orm::c(&WordFromDictionary::difficulty) == difficulty,
                sqlite_orm::c(&WordFromDictionary::language) == language
            )),
        sqlite_orm::limit(wordsNeeded));
    auto initalwordscount2 = m_db.count<WordFromDictionary>();

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

bool UserDatabaseHandle::Authenticate(const std::string& name, const std::string& password)
{
    auto rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
        sqlite_orm::where(
            sqlite_orm::and_(
                sqlite_orm::c(&UserInfo::name) == name,
                sqlite_orm::c(&UserInfo::password) == password
            )));
    if (rows.empty())
    {
        rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
            sqlite_orm::where
            (sqlite_orm::c(&UserInfo::name) == name)
        );
        if (rows.empty())
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
    if (rows.empty())
    {
        //user ul nu exista, username disponibil
        return false;
    }
    return true; //numele exista deja
}

uint16_t UserDatabaseHandle::GetBestScore(const std::string& name) // this should be id not name
{
    auto result = m_db.select(sqlite_orm::columns(&UserInfo::best),
        sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));

    //if (!result.empty()) {
     //   return result.front();
    //}
    return 0;
}

std::deque<int16_t> UserDatabaseHandle::GetLastMatchesPoints(const std::string& name)
{
    auto result = m_db.select(sqlite_orm::columns(&UserInfo::last5),
        sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));

    /*if (!result.empty()) {

        std::string last5String = result.front();

        std::list<int16_t> points;
        size_t pos = 0;
        while ((pos = last5String.find(',')) != std::string::npos) {
            points.push_back(std::stoi(last5String.substr(0, pos)));
            last5String.erase(0, pos + 1);
        }
        points.push_back(std::stoi(last5String));

        return points;
    }*/

    return {};
}

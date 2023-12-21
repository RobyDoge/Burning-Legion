#include"DatabaseHandlers.h"
#include<fstream>
#include <random>
#include<vector>


//WORDDATABASE
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

    inputFile.get();
    inputFile.get();
    inputFile.get();

    inputFile >> language;
    while (inputFile >> word >> difficulty)
    {
        if (!word.compare(language) && difficulty == '3')
            inputFile >> language >> word >> difficulty;
        words.emplace_back(WordFromDictionary{ idCounter++, word, difficulty ,language});
    }

    dictionary.insert_range(words.begin(), words.end());
}

void WordDatabaseHandle::Init()
{
    time_t lastModifiedTime = 1702233024;            //will fix this magic number
    if (hasFileChanged("input.txt", lastModifiedTime))
        m_db.remove_all<WordFromDictionary>();
    m_db.sync_schema();

    auto initalwordscount = m_db.count<WordFromDictionary>();

    if (initalwordscount == 0)
        PopulateDictionaryFromFile(m_db, "input.txt");
}


std::queue<std::string> WordDatabaseHandle::SelectWords(uint8_t numberOfPlayers, uint8_t difficulty, uint8_t language)
{
    std::queue<std::string> generatedWords;

    std::string languageName;
    switch (language)                   //transforming the language from int to the char in the database
    {
    case 0:
        languageName = "eng";
        break;
    case 1:
        languageName = "ro";
        break;
    case 2:
        languageName = "esp";
    default:
        break;
    }

    decltype(m_db.select(sqlite_orm::columns(&WordFromDictionary::id))) rows;


    if(difficulty!= 3)
    {
	    rows = m_db.select(sqlite_orm::columns(&WordFromDictionary::id),
		   sqlite_orm::where(
			   sqlite_orm::and_(
				   sqlite_orm::c(&WordFromDictionary::difficulty) == difficulty + '0',
				   sqlite_orm::c(&WordFromDictionary::language) == languageName
			   )));
    }
    else
    {
        rows = m_db.select(sqlite_orm::columns(&WordFromDictionary::id),
            sqlite_orm::where(
                    sqlite_orm::c(&WordFromDictionary::language) == languageName
                ));
    }

    std::vector<uint16_t> wordIds;

    for (const auto& row : rows)
    {
        wordIds.emplace_back(std::get<0>(row));
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<std::size_t> dis(0, wordIds.size() - 1);

    std::set<std::size_t> chosenIndices;

    while (chosenIndices.size() < numberOfPlayers * 4 + 2)  //create variable for number of turns pls uwu Roby
    {
        auto index = dis(gen);
        if (chosenIndices.insert(index).second)
        {
            auto elements = m_db.select(sqlite_orm::columns(&WordFromDictionary::word),
                sqlite_orm::where(
                    sqlite_orm::c(&WordFromDictionary::id) == wordIds[index]
                    )
            );

            for (const auto& element : elements)
            {
                generatedWords.emplace(std::get<0>(element));
            }
        }
    }

    return generatedWords;
}

bool WordDatabaseHandle::IsInitialized()
{
    return m_db.count<WordFromDictionary>();
}

void WordDatabaseHandle::ClearDictionary()
{
    m_db.remove_all<WordFromDictionary>();
}


//USERDATABASE
void AddNewUser(UserDatabase& users, const std::string name, const std::string& password)
{
    uint16_t idCounter = 1;
    users.insert(UserInfo{ idCounter, name, password, '0' });
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
            //Player ul exista dar nu a pus bine parola
            return false;
        }
        //Player ul nu exista
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
        //Player ul nu exista, username disponibil
        return true;
    }
    return false; //numele exista deja
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
    //auto result = m_db.select(sqlite_orm::columns(&UserInfo::last5),
      //  sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));

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

void UserDatabaseHandle::ClearUserDatabase()
{
    m_db.remove_all<UserInfo>();
}

void UserDatabaseHandle::ClearMatchDatabase()
{
    m_db.remove_all<MatchData>();
}



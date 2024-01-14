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

	if (time_t lastModifiedTime = 1702233024; 
        HasFileChanged("input.txt", lastModifiedTime))
        m_db.remove_all<WordFromDictionary>();
    m_db.sync_schema();

    if ( m_db.count<WordFromDictionary>() == 0)
        PopulateDictionaryFromFile(m_db, "input.txt");
}


std::vector<std::string> WordDatabaseHandle::SelectWords(const uint8_t numberOfPlayers, const uint8_t difficulty, const uint8_t language)
{
    std::vector<std::string> generatedWords;

    const std::string languageName = LANGUAGE_TO_STRING.at(language);

    decltype(m_db.select(sqlite_orm::columns(&WordFromDictionary::id))) rows;

    if(difficulty)
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
	    if (auto index = dis(gen); 
            chosenIndices.insert(index).second)
        {
	        for (auto elements = m_db.select(sqlite_orm::columns(&WordFromDictionary::word),
	                                         sqlite_orm::where(
		                                         sqlite_orm::c(&WordFromDictionary::id) == wordIds[index]
	                                         )
	             ); const auto& element : elements)
            {
                generatedWords.emplace_back(std::get<0>(element));
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
void AddNewUser(UserDatabase& users, const std::string& name, const std::string& password)
{
	constexpr uint16_t idCounter = 1;
    users.insert(UserInfo{ idCounter, name, password, 0 });
}

void UserDatabaseHandle::AddUser(const std::string& name, const std::string& password)
{
    m_db.sync_schema();
    AddNewUser(m_db, name, password);
}

bool UserDatabaseHandle::Authenticate(const std::string& name, const std::string& password)
{
	if (auto rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
	                            sqlite_orm::where(
		                            sqlite_orm::and_(
			                            sqlite_orm::c(&UserInfo::name) == name,
			                            sqlite_orm::c(&UserInfo::password) == password
		                            )));
		rows.empty())
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
	return true; //username ul si parola exista
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

    if (result.empty())
	{
		throw std::runtime_error("User not found");
	}
	else if (result.size() > 1)
	{
		throw std::runtime_error("Multiple users with the same name");
	}
    else
	{
		return std::get<0>(result.front());
	}
}


std::vector<Images> UserDatabaseHandle::GetLast5Matches(const std::string& name)
{
	const auto nameCheck = m_db.select(sqlite_orm::columns(&UserInfo::id),
	                                   sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));

	if (nameCheck.size() == 0)
	{
		throw std::runtime_error("User not found");
	}
	else if (nameCheck.size() > 1)
	{
		throw std::runtime_error("Multiple users with the same name");
	}
	else
	{
		const auto result = m_db.select(sqlite_orm::columns(&MatchData::score ,&MatchData::firstRoundImage, &MatchData::secondRoundImage, &MatchData::thirdRoundImage, &MatchData::forthRoundImage ),
		                                sqlite_orm::where(sqlite_orm::c(&MatchData::uid) == std::get<0>(nameCheck.front())),
		                                sqlite_orm::order_by(&MatchData::id)
		);

		std::vector<Images> images;
		for (const auto& row : result)
		{
			const int16_t score = std::get<0>(row);
			images.push_back(Images{ score,std::get<1>(row), std::get<2>(row), std::get<3>(row), std::get<4>(row)});
		}
		return images;
	}
}

void UserDatabaseHandle::AddMatch(const std::string& name, const int16_t score, const std::string& firstRoundImage, const std::string& secondRoundImage, const std::string& thirdRoundImage, const std::string& forthRoundImage)
{
	const uint16_t idCounter = '1';
    m_db.sync_schema();
	const auto nameCheck = m_db.select(sqlite_orm::columns(&UserInfo::id),
	                                   sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));
    if (nameCheck.empty())
    {
        throw std::runtime_error("User not found");
    }
    else if (nameCheck.size() > 1)
    {
        throw std::runtime_error("Multiple users with the same name");
    }
    else
    {

        m_db.insert(MatchData{ idCounter, std::get<0>(nameCheck.front()), score, firstRoundImage, secondRoundImage, thirdRoundImage, forthRoundImage});
    }


	const auto rows = m_db.select(sqlite_orm::columns(&MatchData::id),
	                              sqlite_orm::where
	                              (sqlite_orm::c(&MatchData::id) == std::get<0>(nameCheck.front()))
	);
    if (rows.size() > 5)
    {
        //if the user has more than 5 matches, delete the one with the lowest id - so the oldest one
        m_db.remove<MatchData>(sqlite_orm::where(sqlite_orm::c(&MatchData::id) == sqlite_orm::min(&MatchData::id)));
    }
}

void UserDatabaseHandle::AddBestScore(const std::string& name, int16_t int16)
{
	const auto rows = m_db.select(sqlite_orm::columns(&UserInfo::id),
	                              sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));
	if (rows.empty())
	{
		throw std::runtime_error("User not found");
	}
	else if (rows.size() > 1)
	{
		throw std::runtime_error("Multiple users with the same name");
	}
	else
	{
		m_db.update_all(sqlite_orm::set(sqlite_orm::c(&UserInfo::best) = int16),
			sqlite_orm::where(sqlite_orm::c(&UserInfo::id) == std::get<0>(rows.front())));
	}
}

void UserDatabaseHandle::UpdateBestScore(const std::string& name, const int16_t score)
{
	const auto rows = m_db.select(sqlite_orm::columns(&UserInfo::best),
	                              sqlite_orm::where(sqlite_orm::c(&UserInfo::name) == name));
    if (rows.empty())
    {
        throw std::runtime_error("User not found");
    }
    else if (rows.size() > 1)
    {
        throw std::runtime_error("Multiple users with the same name");
    }
    else
    {
        if (score > std::get<0>(rows.front()))
        {
           AddBestScore(name, score);
        }
    }
}

void UserDatabaseHandle::ClearUserDatabase()
{
    ClearMatchDatabase();
    m_db.remove_all<UserInfo>();
}

void UserDatabaseHandle::ClearMatchDatabase()
{
    m_db.remove_all<MatchData>();
}
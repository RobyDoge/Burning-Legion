#pragma once
#define DATABASE_HANDLERS_H
#include <string>
#include <queue>
#include <filesystem>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include <unordered_map>

namespace fs = std::filesystem;
namespace sql = sqlite_orm;

//used for file cheking
inline bool HasFileChanged(const std::string& filename, time_t& lastModifiedTime) {
	struct stat fileStat;

	if (stat(filename.c_str(), &fileStat) != 0) {
		 //Error handling: Unable to get file status
		std::cerr << "Error: Unable to get file status." << std::endl;
		return false;
	}

	 //Compare current modification time with the previous one
	if (fileStat.st_mtime != lastModifiedTime) {
		lastModifiedTime = fileStat.st_mtime; // Update last modified time
		return true; // File has been modified
	}

	return false; // File has not been modified
}			

//structure that will contain the words from our database
struct WordFromDictionary
{
	uint16_t id;
	std::string word;
	uint8_t difficulty;
	std::string language;
};

//structure for user information
struct UserInfo
{
	uint16_t id;
	std::string name;
	std::string password;
	int16_t best;
};

//structure for storing the images and the score
struct MatchData
{
	uint64_t id;
	uint16_t uid;
	int32_t score;
	std::string firstRoundImage;
	std::string secondRoundImage;
	std::string thirdRoundImage;
	std::string forthRoundImage;
};

//creating database for dictionary
inline auto CreateDictionary(const std::string& filename)		
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Words",
			sql::make_column("id", &WordFromDictionary::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &WordFromDictionary::word),
			sql::make_column("difficulty", &WordFromDictionary::difficulty),
			sql::make_column("language", &WordFromDictionary::language)
		)
	);
}

//creating database for users (tables for information and matches list)
inline auto CreateUserDatabase(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"User",
			sql::make_column("id", &UserInfo::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &UserInfo::name),
			sql::make_column("password", &UserInfo::password),
			sql::make_column("best", &UserInfo::best)
		),
		sql::make_table(
			"Match",
			sql::make_column("id", &MatchData::id, sql::primary_key().autoincrement()),
			sql::make_column("uid", &MatchData::uid, sql::foreign_key(&UserInfo::id).references(&MatchData::uid)),		
			sql::make_column("score", &MatchData::score),
			sql::make_column("firstRoundImage", &MatchData::firstRoundImage),
			sql::make_column("secondRoundImage", &MatchData::secondRoundImage),
			sql::make_column("thirdRoundImage", &MatchData::thirdRoundImage),
			sql::make_column("forthRoundImage", &MatchData::forthRoundImage)
		)
	);

}

using Dictionary = decltype(CreateDictionary(""));
using UserDatabase = decltype(CreateUserDatabase(""));

void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename);		//adding all the words to the database
void AddNewUser(Dictionary& dictionary, const std::string& filename);						//ading one user at a time in the UserInfo table

//word database class:
// - calls PopulateDictionaryFromFile method via Init()
// - could empty database if needed via ClearDictionary()
// - getting the needed word list via SelectWords()
class WordDatabaseHandle
{
public:

	void Init();
	std::queue<std::string> SelectWords(uint8_t numberOfPlayers, uint8_t difficulty, uint8_t language);
	bool IsInitialized();
	void ClearDictionary();

private:
	Dictionary m_db = CreateDictionary("database.sqlite");
	static constexpr std::unordered_map<uint8_t, std::string> LANGUAGE_TO_STRING
	{
		{0, "eng"},
		{1, "ro"},
		{2, "esp"}
	};
};


class UserDatabaseHandle
{
public:
	void AddUser(const std::string& name, const std::string& password);
	std::vector<std::string> SelectUserInfo(const uint8_t wordsNeeded);
	bool Authenticate(const std::string& name, const std::string& password);
	bool CheckUsername(const std::string& name);
	uint16_t GetBestScore(const std::string& name);
	std::deque<int16_t> GetLastMatchesPoints(const std::string& name);

	void ClearUserDatabase();
	void ClearMatchDatabase();

private:
	UserDatabase m_db = CreateUserDatabase("userDatabase.sqlite");
};

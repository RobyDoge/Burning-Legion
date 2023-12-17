#pragma once
#define DATABASE_HANDLERS_H
#include <string>
#include <queue>
#include <filesystem>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

namespace fs = std::filesystem;
namespace sql = sqlite_orm;

inline bool hasFileChanged(const std::string& filename, time_t& lastModifiedTime) {
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

struct WordFromDictionary									//structure that will contain the words from our database
{
	uint16_t id;
	std::string word;
	uint8_t difficulty;
	std::string language;
};

struct UserInfo
{
	uint16_t id;
	std::string name;
	std::string password;
	//std::string last5;
	int16_t best;
};

struct MatchData
{
	uint64_t id;
	uint16_t uid;
	int32_t score;
	std::string R1IMG;
	std::string R2IMG;
	std::string R3IMG;
	std::string R4IMG;
};

inline auto CreateDictionary(const std::string& filename)		//creating database for dictionary
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
			sql::make_column("uid", &MatchData::uid, sql::foreign_key(&UserInfo::id).references(&MatchData::uid)),		//cannot make this foreign key explicitly
			sql::make_column("score", &MatchData::score),
			sql::make_column("R1IMG", &MatchData::R1IMG),
			sql::make_column("R2IMG", &MatchData::R2IMG),
			sql::make_column("R3IMG", &MatchData::R3IMG),
			sql::make_column("R4IMG", &MatchData::R4IMG)
		)
	);

}

using Dictionary = decltype(CreateDictionary(""));
using UserDatabase = decltype(CreateUserDatabase(""));

void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename);
void AddNewUser(Dictionary& dictionary, const std::string& filename);
Dictionary& CreateDatabase();

class WordDatabaseHandle
{
public:

	void Init();
	std::queue<std::string> SelectWords(uint8_t wordsNeeded, uint8_t difficulty, uint8_t language); //game_logic::Lobby::GameDifficulty difficulty);

	void ClearDictionary();

//private:
	Dictionary m_db = CreateDictionary("database.sqlite");
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


private:
	UserDatabase m_db = CreateUserDatabase("userDatabase.sqlite");
};

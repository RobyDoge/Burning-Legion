#pragma once
#define DATABASE_HANDLERS_H

#include <string>
#include <vector>
#include <filesystem>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

namespace fs = std::filesystem;
namespace sql = sqlite_orm;


struct WordFromDictionary									//structure that will contain the words from our database
{
	uint16_t id;
	std::string word;
	uint8_t difficulty;
};

inline auto CreateDictionary(const std::string& filename)		//creating database for dictionary
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Words",
			sql::make_column("id", &WordFromDictionary::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &WordFromDictionary::word),
			sql::make_column("difficulty", &WordFromDictionary::difficulty)
		)
	);
}

inline bool hasFileChanged(const std::string& filename, time_t& lastModifiedTime) {
	struct stat fileStat;

	if (stat(filename.c_str(), &fileStat) != 0) {
		// Error handling: Unable to get file status
		std::cerr << "Error: Unable to get file status." << std::endl;
		return false;
	}

	// Compare current modification time with the previous one
	if (fileStat.st_mtime != lastModifiedTime) {
		lastModifiedTime = fileStat.st_mtime; // Update last modified time
		return true; // File has been modified
	}

	return false; // File has not been modified
}


using Dictionary = decltype(CreateDictionary(""));

void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename);
Dictionary& CreateDatabase();

class WordDatabaseHandle
{
public:
	void init();
	std::vector<std::string> SelectWords(const uint8_t wordsNeeded);
	void ClearDictionary();

private:
	Dictionary m_db = CreateDictionary("database.sqlite");
};

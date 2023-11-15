

#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

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

using Dictionary = decltype(CreateDictionary(""));

void PopulateDictionaryFromFile(Dictionary& dictionary, const std::string& filename);
Dictionary& CreateDatabase();


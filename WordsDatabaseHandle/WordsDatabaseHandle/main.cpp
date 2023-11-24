#include "WordDatabaseHandle.h"
#include <string>
#include <vector>

int main()
{
	WordDatabaseHandle handle;
	handle.init();
	std::vector<std::string> words = handle.SelectWords(2);
	return 0;
}
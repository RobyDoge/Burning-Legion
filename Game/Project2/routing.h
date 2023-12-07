#include <crow.h>
#include "DatabaseHandlers.h"

namespace http
{
	class Routing
	{
	public:
		void Run(WordDatabaseHandle& wordStorage, UserDatabaseHandle& userStorage);		//Creates all the paths and stuff

	private:

	private:
		crow::SimpleApp m_app;
	};
}
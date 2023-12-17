/*
 *the main function of the server
 *should be this
#include "routing.h"
using namespace server;
int main()
{
	
	GameHandler handler{};
	Routing r{ handler };
	r.run(
	//other necessary params for this function
	);

	return 0;
}
*/

/*
 * for testing
 * the next main function should be used
 * after testing all the functions, the main function should be changed to the one above
 * to be created a list of all the functions that have been tested
 */

#include "routing.h"
#include "DatabaseHandlers.h"
#include <memory>

import lobby;
using namespace server;
int main()
{
	/*
	 *testing environment
	 */
	UserDatabaseHandle userHandler;
	WordDatabaseHandle wordHandler;

	Routing r;
	r.Run(wordHandler,userHandler);
	return 67;
}
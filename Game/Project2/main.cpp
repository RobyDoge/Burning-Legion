/*
 *the main function of the server
 *should be this
#include "routing.h"
using namespace server;
int main()
{
	Routing r;
	r.run(
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

using namespace server;
int main()
{
	UserDatabaseHandle udbh;
	udbh.ClearUserDatabase();

	/*
	 *testing environment
	 */
	
	Routing r;
	r.Run();
	return 9;
}
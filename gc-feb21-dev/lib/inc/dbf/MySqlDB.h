
#include <mysql++.h>
#include <string>
#include "IDBConnect.h"
#include "common.h"
#include "DataTable.h"	// To store the rows in form of tables
#include "DataColumn.h" // TO store the columns in form of columns
#include "exceptions.h"
#include "noexceptions.h"
#include "DAOConnectionException.h" // Connection Exceptions
#include "DAOQueryException.h"		// Query Exception

/** @File : DAOManager
*   @Author : AnmadeusCPP
*   @Brief : It is an class uthat inherits IDBConnect class and performs funtion like making and delete connection along with execiting a query and non-query
*/

using namespace std;

namespace gc
{
	namespace db
	{
		class MySqlDB : public IDBConnect
		{
			string dbName;
			string IPAddress;
			string UserName;
			string Password;
			int a;
			mysqlpp::Connection conn;

		public:
			/** @Brief :Used to create a Connection with the database.
					* @param : DataBase, IPAddress Username and password
					*
					*/
			MySqlDB(string _dbName, string _IPAddress, string _UserName, string _Password);
			/** @Brief :Used to make a Connection with the database.
					*  @param : 
					* @return : int
					*/
			int getConnection();
			/** @Brief :Used to create a Connection with the database.
					* @param : 
					* @return : int
					*/
			int closeConnection();
			/** @Brief :Used to execute a query i.e. Select statements.
					* @param : query
					* @return : DataTable pointer
					*/
			DataTable *execQuerry(string querry);
			/** @Brief :Used to create a Connection with the database.
					* @param : string of query
					* @return : int
					*/
			int execNonQuerry(string querry);
			/** @Brief :Used to delete a Connection with the database.
					* @param : 
					* @return :
					*/
			~MySqlDB();
		};
	} // namespace db
} // namespace gc

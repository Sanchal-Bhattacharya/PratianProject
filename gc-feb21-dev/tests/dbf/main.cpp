#include "DBManager.h"
#include "DataTable.h"
#include <stdexcept>
#include <sstream>
using namespace gc;
using namespace db;
using namespace std;
IDBConnect *obj = DBManager::getIDBConnect();

/*void doThis()
{
	int i;
	for(i=11;i<20;i++)
	{
		stringstream ss;
		ss.clear();
		ss.str(string(""));
		ss << "INSERT INTO TEMP VALUES ("<<i<<",'Gaurav')"; 
		const string &temp = ss.str();
		obj->execNonQuerry(temp);
	}
}

void doThat()
{
	int i;
	for(i=1;i<10;i++)
	{
		stringstream ss;
		ss.clear();
		ss.str(string(""));
		ss << "INSERT INTO TEMP VALUES ("<<i<<",'Hemant')"; 
		const string &temp = ss.str();
		obj->execNonQuerry(temp);
	}
}
*/
int main()
{

	
	try
	{
	
	/*boost::thread thread1(doThis);
	boost::thread thread2(doThat);
	thread1.join();
	thread2.join();
	return 0;
	*/	//obj->getConnection();
		//obj->execNonQuerry("DELETE FROM COUNTRIES WHERE COUNTRY_ID = 'BG' OR COUNTRY_ID = 'RS'");
		//obj->execNonQuerry("INSERT INTO TEMP2 VALUES (4,'Ankita');INSERT INTO TEMP2 VALUES (5,'Gurpreet');");
		//DataTable* table = obj->execQuerry("SELECT COUNTRY_NAME, REGION_ID FROM COUNTRIES");
		
		//vector<DataTable::DataRow *> rows = table->getRows();
		

		//cout<<rows.size()<<table->getNumberOfColumns()<<endl;
		//for(int i=0; i< rows.size() ; i++)
	//	{
			//cout<<rows[i]->getColumn<string,STRING>(0)<<  rows[i]->getColumn<int,INT>(1) <<endl;//  << rows[i]->getColumn<string,STRING>(1)endl;int,INT
		//}
		//delete table;

		//obj->getConnection();
		//obj->execNonQuerry("DELETE FROM COUNTRIES WHERE COUNTRY_ID = 'BG' OR COUNTRY_ID = 'RS'");
		//obj->execNonQuerry("INSERT INTO TEMP2 VALUES (4,'Ankita');INSERT INTO TEMP2 VALUES (5,'Gurpreet');");
		/*DataTable* table = obj->execQuerry("SELECT COUNTRY_NAME, REGION_ID FROM COUNTRIES WHERE COUNTRY_ID='TT'");
		
		vector<DataTable::DataRow *> rows = table->getRows();
		
		cout<<rows.size()<<table->getNumberOfColumns()<<endl;
		for(int i=0; i< rows.size() ; i++)
		{
			cout<<rows[i]->getColumn<string,STRING>(0)<<  rows[i]->getColumn<int,INT>(1) <<endl;//  << rows[i]->getColumn<string,STRING>(1)endl;int,INT
		}
		delete table;
		//obj->closeConnection();
*/
		IDBConnect *obj2 = DBManager::getLoggerDB();
		DataTable* table = obj2->execQuerry("SELECT * FROM LOG_TABLE");
		
		vector<DataTable::DataRow *> rows = table->getRows();
		
		for(int i=0; i< rows.size() ; i++)
		{
			cout<<rows[i]->getColumn<string,STRING>(0)<<  rows[i]->getColumn<string,STRING>(1) <<endl;//  << rows[i]->getColumn<string,STRING>(1)endl;int,INT
		}
		//delete obj;*/
		//obj->execNonQuerry("call sp_create('Hemant','hemant','111')");
	
	}
	catch(DBConfigFileException e)
	{
		cerr<< e.what() << endl;;
	}
	catch(DAOQuerryException e)
	{
		cerr<< e.what() << endl;;
	}
	catch(GCException e)
	{
		cerr<< e.what() << endl;
	}
	catch(exception e)
	{
		cerr<< e.what() << endl;
	}
	return 0;
}

#include "SQLiteDB.h"
using namespace gc;
using namespace gc::db;

int main()
{
	SQLiteDB obj("/home/comp/Project-DBFramework/example.db");
	obj.getConnection();
	obj.execNonQuerry("INSERT INTO TEMP VALUES (100);");
	obj.execQuerry("SELECT * FROM TEMP;");
	obj.closeConnection();
}

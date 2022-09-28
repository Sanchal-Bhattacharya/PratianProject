#include "DBManager.h"
#include "DBFactory.h"

namespace gc
{
	namespace db
	{
		IDBConnect *DBManager::getIDBConnect()
		{
			return (DBFactory::getDBFactoryInstance()->getIDBaseInstance());
		}

		IDBConnect *DBManager::getLoggerDB()
		{
			return (DBFactory::getDBFactoryInstance()->getLogDBaseInstance());
		}
	} // namespace db
} // namespace gc

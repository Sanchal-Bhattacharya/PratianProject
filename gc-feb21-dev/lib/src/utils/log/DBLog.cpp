#include <iostream>

#include "DBLog.h"
#include "GCCommon.h"

using namespace std;
namespace gc
{
	namespace util
	{
		DBLog::DBLog(ALog *successor)
			: ALog(successor), connObj(db::DBManager::getLoggerDB())
		{
		}

		DBLog::~DBLog()
		{
		}

		bool DBLog::SaveLog(LogData &logData)
		{
			try
			{
				connObj->getConnection();

				ss.clear();
				ss.str(string(""));
				ss << "insert into log_table( type_log, tag, pid, datetype, message) values (\"" << logData.getType() << "\", \"";
				ss << logData.getTag() << "\", " << logData.getPId() << ", \"" << logData.getDateTime() << "\", \"";
				ss << logData.getMsg() << "\" )";

				const string &temp = ss.str();
				connObj->execQuery(temp);
			}
			catch (...)
			{
				LogData logData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "<Log>DBLog", " Failed :removing form log chain");
				this->setEnabled(false); //don't change order
				CreateLog(logData);		 //don't change order
				return false;
			}
			return true;
		}

	} // namespace util
} // namespace gc

#include "FileLog.h"
#include <fstream>
#include <iostream>

#include "GCCommon.h"
#include "LogFileException.h"

using namespace std;

namespace gc
{
	namespace util
	{
		std::string const FileLog::defaultFileName = "config";

		FileLog::FileLog(ALog *successor) : ALog(successor)
		{
			string fName = defaultFileName + gc::common::DateTime::getTimeStampSecString() + ".txt";

			try
			{
				fPtr.open(fName.c_str(), ios::in | ios::out);
				if (!fPtr.is_open())
				{
					fPtr.open(fName.c_str(), ios::out);
				}

				if (!fPtr.is_open()) //code handle file open failure
				{
					throw log::LogFileException("<FileLog>Log File Creation Error");
				}
			}
			catch (log::LogFileException E)
			{
				LogData logData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:FileLog", E.what());
				this->setEnabled(false); //don't change order
				CreateLog(logData);		 //don't change order
			}
		}

		FileLog::~FileLog()
		{
			this->successor = NULL;
			if (!fPtr.is_open())
				fPtr.close();
		}

		bool FileLog::SaveLog(LogData &logData)
		{
			if (fPtr.is_open())
			{
				ss.clear();
				ss.str(string(""));
				ss << logData.getType() << '/' << logData.getTag() << '\t' << logData.getPId() << '\t' << logData.getDateTime() << '\t' << logData.getMsg() << '\n';
				const string &temp = ss.str();
				try
				{
					fPtr.write((char *)temp.c_str(), sizeof(char) * temp.length());
					if (fPtr.bad())
						throw log::LogFileException("<FileLog>Write to log file failed(Removing FileLog)");
				}
				catch (log::LogFileException E)
				{
					LogData exclogData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:FileLog", E.what());
					this->setEnabled(false); //don't change order
					CreateLog(exclogData);	 //don't change order
					return false;
				}
			}
			return true;
		}

	} // namespace util
} // namespace gc


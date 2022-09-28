#include "XMLLog.h"
#include <fstream>
#include <iostream>

#include "GCCommon.h"
#include "LogFileException.h"

using namespace std;

namespace gc
{
	namespace util
	{
		std::string const XMLLog::defaultFileName = "/home/sbhattacharya/Downloads/config";
		

		XMLLog::XMLLog(ALog *successor) : ALog(successor)
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
					throw log::LogFileException("<XMLLog>Log File Creation Error");
				}
			}
			catch (log::LogFileException E)
			{
				LogData logData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:XMLLog", E.what());
				this->setEnabled(false); //don't change order
				CreateLog(logData);		 //don't change order
			}
		}

		XMLLog::~XMLLog()
		{
			this->successor = NULL;
			if (!fPtr.is_open())
			{
				fPtr.close();
			}
		}

		bool XMLLog::SaveLog(LogData &logData)
		{
			if (fPtr.is_open())
			{
				ss.clear();
				ss.str(string(""));
				ss << "<XMLlog>\n";
				ss << "\t<type> " << logData.getType() << " </type>" << '\n' << "\t<tag> " << logData.getTag() << " </tag>" << '\n' << "\t<getpid> " << logData.getPId() << " </getpid>" << '\n' << "\t<datetime> " << logData.getDateTime() << " </datetime>" << '\n' << "\t<message> " << logData.getMsg() << " </message>\n\n";
				ss << "</XMLlog>\n";
				
				const string &temp = ss.str();
				
				try
				{
					fPtr.write((char *)temp.c_str(), sizeof(char) * temp.length());
					
					if (fPtr.bad())
						throw log::LogFileException("<XMLLog>Write to log file failed(Removing XMLLog)");

				}
				catch (log::LogFileException E)
				{
					LogData exclogData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:XMLLog", E.what());
					this->setEnabled(false); //don't change order
					CreateLog(exclogData);	 //don't change order
					return false;
				}
			}
			return true;
		}
	}

} // namespace util
 // namespace gc

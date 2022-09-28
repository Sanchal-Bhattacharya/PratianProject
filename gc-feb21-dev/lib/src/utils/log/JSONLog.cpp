#include <fstream>
#include <iostream>
#include "LogFileException.h"
#include "GCCommon.h"

#include "JSONLog.h"

using namespace std;

namespace gc
{
	namespace util
	{
		//config<timestamp>.json
		const string& JSONLog::defaultFileName {"config"};

		JSONLog::JSONLog(ALog *successor): ALog(successor)
		{
			string fName = defaultFileName + gc::common::DateTime::getTimeStampSecString() + ".json";

			try
			{
				fPtr.open(fName.c_str(), ios::in | ios::out);
				if (!fPtr.is_open())
				{
					isNewFile = true;
					fPtr.open(fName.c_str(), ios::out);
					fPtr << "{\"log\":[]}"; //do not edit format for first time open
				}

				if (!fPtr.is_open()) //#############code handle file open failure
				{
					throw log::LogFileException("<JSONLog>Log File Creation Error");
				}
				fPtr.seekp(-2, ios::end); //place file pointer 2 characters back to overwrite ]}catch(log::LogFileException E)
			}
			catch (log::LogFileException E)
			{
				LogData logData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:JSONLog", E.what());
				this->setEnabled(false); //don't change order
				CreateLog(logData);		 //don't change order
			}
		}

		JSONLog::~JSONLog()
		{
			this->successor = NULL;
			if (fPtr.is_open())
			{
				fPtr << "]}";
				fPtr.flush();
				fPtr.close();
			}
		}

		bool JSONLog::SaveLog(LogData &logData)
		{
			try
			{
				parseDataToBuffer(logData);
				if (false == isNewFile)
					fPtr << ',';

				isNewFile = false;
				const string &temp = buffer.GetString();
				fPtr.write((char *)temp.c_str(), sizeof(char) * temp.length());
				if (fPtr.bad())
					throw log::LogFileException("<JSONLog>Write to log file failed(Removing JSONLog)");
			}
			catch (log::LogFileException E)
			{
				LogData logData("Fatal", common::Process::getPId(), common::DateTime::getTimeStampMicroString(), "Log:JSONLog", E.what());
				this->setEnabled(false); //don't change order
				CreateLog(logData);		 //don't change order
				return false;
			}
			return true;
		}

		void JSONLog::parseDataToBuffer(LogData &logData)
		{
			buffer.Clear();
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			writer.StartObject();
			writer.String("type");
			writer.String(logData.getType().c_str());
			writer.String("tag");
			writer.String(logData.getTag().c_str());
			writer.String("dt");
			writer.String(logData.getDateTime().c_str());
			writer.String("pid");
			writer.Int(logData.getPId());
			writer.String("msg");
			writer.String(logData.getMsg().c_str());
			writer.EndObject();
		}

	} // namespace util
} // namespace gc

#include <algorithm>
#include <string>
#include <unistd.h>

#include <rapidjson/filereadstream.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include "ALog.h"
#include "ConsoleLog.h"
#include "FileLog.h"
#include "JSONLog.h"
#include "LogData.h"
#include "XMLLog.h"
#include "DBLog.h"
#include "LogConfigFileException.h"
#include "GCCommon.h"

#include "LogFactory.h"

using namespace std;
using namespace rapidjson;

namespace gc
{
	namespace util
	{

		const std::string LogFactory::DefaultConfig = " { "
													  " \"type\":[\"console\"] "
													  " } ";

		const std::string LogFactory::ConfigFileName = "logconfig.json";

		LogFactory LogFactory::factInstance;

		LogFactory::LogFactory() : iLogChain(NULL)
		{
		}

		LogFactory::LogFactory(LogFactory &logFact)
		{
		}

		LogFactory::~LogFactory()
		{
			ALog *temp = iLogChain;
			while (NULL != temp)
			{
				temp = (iLogChain)->getSuccessor();
				delete iLogChain;
				iLogChain = temp;
			}
		}

		LogFactory *LogFactory::getInstance()
		{
			return &factInstance;
		}

		ILog *LogFactory::getLogChain()
		{
			LogData logData;
			logData.setTag("Log");
			logData.setPId(getpid());

			if (iLogChain == NULL) // check if chain of loggers exist or not
			{
				//ConsoleLog moves to end of the Log chain
				//Log Errors propagating durind Logging will always logged to console
				iLogChain = new ConsoleLog(NULL); // default ConsoleLog is always instantiated

				FILE *iFile = fopen(ConfigFileName.c_str(), "r"); //open configuration file

				if (NULL == iFile) // configuration file fails to open : use default config
				{
					logData.setDateTime(gc::common::DateTime::getTimeStampMicroString());

					logData.setMsg("Failed to open configuration file : " + ConfigFileName);
					logData.setTag("Warn");
					iLogChain->CreateLog(logData);

					logData.setMsg("Switching to default configuration ");
					iLogChain->CreateLog(logData);

					logData.setMsg(DefaultConfig);
					iLogChain->CreateLog(logData);
				}
				else
				{
					//read config file and create appropriate log instances
					
					std::vector<string> loggerList = getLoggerListFromConfig(iFile);
					for (std::vector<string>::iterator iter = loggerList.begin(); iter != loggerList.end(); iter++)
					{	
						//iLogChain = new XMLLog(iLogChain);
						

						if (*iter == "txt")
						{
							
							iLogChain = new FileLog(iLogChain);
						}
						else if (*iter == "json")
						{
							iLogChain = new JSONLog(iLogChain);
						}
						else if (*iter == "xml")
						{
							iLogChain = new XMLLog(iLogChain);
						}
						else if (*iter == "db")
						{
							iLogChain = new DBLog(iLogChain);
						}
						else if (*iter == "console") // already initialized
							;
						
						else
						{
							logData.setMsg("Invalid Log Type : " + *iter);
							iLogChain->CreateLog(logData);
						}
					}

					if (NULL != iFile)
						fclose(iFile);
					iFile = NULL;
				}
			}
			return iLogChain;
		}

		std::vector<string> LogFactory::getLoggerListFromConfig(FILE *iFile)
		{
			std::vector<string> loggerList;
			Document document;

			try
			{
				if (NULL == iFile)
				{
					rapidjson::StringStream ss(DefaultConfig.c_str());
					document.ParseStream(ss);
				}
				else
				{
					char *readBuffer = new char[CHAR_BUFFER_SIZE];

					if (NULL == readBuffer)
						; //## needs implementation
					FileReadStream readStream(iFile, readBuffer, sizeof(readBuffer));
					document.ParseStream(readStream);
					delete readBuffer;
					readBuffer = NULL;
				}

				if (document.HasParseError())
					throw log::LogConfigFileException("<LogFactory>Failed to parse JSON configuration file");
				if (false == document.HasMember("type"))
					throw log::LogConfigFileException("<LogFactory>Failed to find tag:\'type\' in configuration file");

				const Value &a = document["type"];
				if (false == a.IsArray())
					throw log::LogConfigFileException("<LogFactory>\'type\' is not an array in configuration file");
				for (SizeType i = 0; i < a.Size(); i++)
				{
					if (a[i].IsString())
						if (!(std::find(loggerList.begin(), loggerList.end(), a[i].GetString()) != loggerList.end()))
						{
							loggerList.push_back(a[i].GetString());
						}
				}
			}
			catch (log::LogConfigFileException E)
			{
				LogData logData;
				logData.setType("Fatal");
				logData.setTag("Log");
				logData.setPId(getpid());

				logData.setDateTime(gc::common::DateTime::getTimeStampMicroString());
				logData.setMsg(E.what());
				iLogChain->CreateLog(logData);

				logData.setType("Info");
				logData.setDateTime(gc::common::DateTime::getTimeStampMicroString());
				logData.setMsg("<LogFactory>Switching to default configuration ");
				iLogChain->CreateLog(logData);
			}
			catch (...)
			{
				LogData logData;
				logData.setType("Fatal");
				logData.setDateTime(gc::common::DateTime::getTimeStampMicroString());
				logData.setTag("Log");
				logData.setPId(getpid());
				logData.setDateTime(gc::common::DateTime::getTimeStampMicroString());
				logData.setMsg("<LogFactory>Uncaught Exception::Running on default configuration ");
				iLogChain->CreateLog(logData);
			}
			return loggerList;
		}
	} // namespace util
} // namespace gc

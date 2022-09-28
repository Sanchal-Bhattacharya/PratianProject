#include <iostream>
#include "LogManager.h"

namespace gc
{
	namespace util
	{
		LogManager LogManager::logMgrInstance;

		LogManager *LogManager::getInstance()
		{
			return &logMgrInstance;
		}

		LogManager::LogManager()
		{
			LogFactory *factory = LogFactory::getInstance();
			logList = factory->getLogChain();	
		}

		LogManager::~LogManager()
		{
			logList = NULL;
		}

		bool LogManager::CreateLog(LogData logData)
		{
			if (NULL != logList)
				return logList->CreateLog(logData);
			return false;
		}

	} // namespace util
} // namespace gc

#pragma once
#include "ALog.h"
#include "ILog.h"
#include "LogData.h"
#include "LogFactory.h"

using namespace std;

namespace gc
{
	namespace util
	{
		
		class LogManager
		{
			ILog *logList;
			LogManager();
			~LogManager();

			static LogManager logMgrInstance;
		public:
			static LogManager *getInstance();
			bool CreateLog(LogData logData);
		};
	} // namespace util
} // namespace gc

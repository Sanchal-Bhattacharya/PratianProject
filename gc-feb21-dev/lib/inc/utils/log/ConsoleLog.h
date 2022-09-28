#pragma once
#include "ALog.h"
#include "LogData.h"

namespace gc
{
	namespace util
	{
		class ConsoleLog : public ALog
		{
		public:
			ConsoleLog(ALog *);
			~ConsoleLog();

			bool SaveLog(LogData &logData);
		};

	} // namespace util
} // namespace gc

#pragma once
#include <sstream>
#include "ALog.h"
#include "LogData.h"
#include "DBManager.h"

namespace gc
{
	namespace util
	{
		class DBLog : public ALog
		{
			std::stringstream ss;
			db::IDBConnect *connObj;

		public:
			DBLog(ALog *);
			~DBLog();

			bool SaveLog(LogData &logData);
		};

	} // namespace util
} // namespace gc

#pragma once
#include <fstream>
#include <sstream>

#include "ALog.h"
#include "LogData.h"

namespace gc
{
	namespace util
	{
		class FileLog : public ALog
		{
			std::stringstream ss;
			static std::string const defaultFileName;
			std::ofstream fPtr;

			public:
			
			FileLog(ALog *successor);
			~FileLog();

			bool SaveLog(LogData &logData);
		};

	} // namespace util
} // namespace gc



#pragma once
#include <fstream>
#include <sstream>
#include "ALog.h"
#include "LogData.h"

namespace gc
{
	namespace util
	{
		class XMLLog : public ALog
		{
			std::stringstream ss;
			static std::string const defaultFileName;
			std::ofstream fPtr;

			public:
			
			XMLLog(ALog *iLog);
			~XMLLog();

			bool SaveLog(LogData &logData);
		};
	} // namespace util
} // namespace gc

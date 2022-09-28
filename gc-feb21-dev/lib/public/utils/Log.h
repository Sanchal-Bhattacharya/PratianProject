#pragma once
#include <string>

#include "LogData.h"

#define MAX_LOG_TAG_SIZE 20
#define MAX_LOG_MSG_SIZE 160

namespace gc
{
	namespace util
	{
		class Log
		{
			Log();
			~Log();
			static LogData logData;

		public:
			static void Fatal(std::string tag, std::string msg);
			static void Error(std::string tag, std::string msg);
			static void Warn(std::string tag, std::string msg);
			static void Info(std::string tag, std::string msg);
			static void Debug(std::string tag, std::string msg);
		};
	} // namespace util
} // namespace gc

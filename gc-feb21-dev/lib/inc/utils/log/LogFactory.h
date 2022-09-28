#pragma once

#include <vector>
#include <string>

#include "ILog.h"

namespace gc
{
	namespace util
	{
		class ConsoleLog;
		class FileLog;

		class LogFactory
		{
			static const int CHAR_BUFFER_SIZE = 4096;

			static const std::string DefaultConfig;
			static const std::string ConfigFileName;

			static LogFactory factInstance;

			ALog *iLogChain;

			LogFactory();
			LogFactory(LogFactory &);
			~LogFactory();

			std::vector<std::string> getLoggerListFromConfig(FILE *iFile);

		public:
			static LogFactory *getInstance();

			ILog *getLogChain();
		};
	} // namespace util
} // namespace gc

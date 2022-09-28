#pragma once
#include <fstream>
#include <string>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "ALog.h"
#include "LogData.h"

namespace gc
{
	namespace util
	{
		class JSONLog : public ALog
		{
			bool isNewFile;
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer;
			std::fstream fPtr;

			static const std::string& defaultFileName;
			void parseDataToBuffer(LogData &logData);

		public:
			JSONLog(ALog *iLog);
			~JSONLog();

			bool SaveLog(LogData &logData);
		};
	} // namespace util
} // namespace gc

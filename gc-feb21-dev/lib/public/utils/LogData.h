#pragma once
#include <string>

namespace gc
{
	namespace util
	{
		class LogData
		{
			std::string type = "";
			int pId = 0;
			std::string dateTime = "";
			std::string tag = "";
			std::string msg = "";

		public:
			LogData();
			LogData(std::string type, int pId, std::string dataTime, std::string tag, std::string msg);
			~LogData();

			int &getPId();
			void setPId(int PId);

			std::string &getType();
			void setType(std::string type);

			std::string &getDateTime();
			void setDateTime(std::string dateTime);

			std::string &getTag();
			void setTag(std::string tag);

			std::string &getMsg();
			void setMsg(std::string msg);
		};
	} // namespace util
} // namespace gc

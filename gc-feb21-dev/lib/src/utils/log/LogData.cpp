#include <string>
#include "LogData.h"

using namespace std;

namespace gc
{
	namespace util
	{

		LogData::LogData()
			: type(""), pId(0), dateTime(""), tag(""), msg("")
		{
		}

		LogData::~LogData()
		{
		}

		LogData::LogData(std::string type, int pId, std::string dateTime, std::string tag, std::string msg)
			: type(type), pId(pId), dateTime(dateTime), tag(tag), msg(msg)
		{
		}

		int &LogData::getPId()
		{
			return pId;
		}

		void LogData::setPId(int pId)
		{
			this->pId = pId;
		}

		std::string &LogData::getType()
		{
			return this->type;
		}

		void LogData::setType(std::string type)
		{
			this->type = type;
		}

		std::string &LogData::getDateTime()
		{
			return dateTime;
		}

		void LogData::setDateTime(std::string dateTime)
		{
			this->dateTime = dateTime;
		}

		std::string &LogData::getTag()
		{
			return tag;
		}

		void LogData::setTag(std::string tag)
		{
			this->tag = tag;
		}

		std::string &LogData::getMsg()
		{
			return msg;
		}

		void LogData::setMsg(std::string msg)
		{
			this->msg = msg;
		}
	} // namespace util
} // namespace gc

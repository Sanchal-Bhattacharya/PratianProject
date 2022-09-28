#include <iostream>
#include "Log.h"
#include "LogManager.h"
#include "GCCommon.h"

namespace gc
{
	namespace util
	{
		LogData Log::logData{};

		Log::Log()
		{
		}

		Log::~Log()
		{
		}

		void Log::Fatal(std::string tag, std::string msg)
		{
			LogManager *logManager = LogManager::getInstance();
			logData.setType("Fatal");
			logData.setPId(common::Process::getPId());
			logData.setDateTime(common::DateTime::getTimeStampMicroString());

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_TAG_SIZE));
			logData.setTag(tag);

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_MSG_SIZE));
			logData.setMsg(msg);

			logManager->CreateLog(logData);
		}

		void Log::Error(std::string tag, std::string msg)
		{
			LogManager *logManager = LogManager::getInstance();
			logData.setType("Error");
			logData.setPId(common::Process::getPId());
			logData.setDateTime(common::DateTime::getTimeStampMicroString());

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_TAG_SIZE));
			logData.setTag(tag);

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_MSG_SIZE));
			logData.setMsg(msg);

			logManager->CreateLog(logData);
		}

		void Log::Warn(std::string tag, std::string msg)
		{
			LogManager *logManager = LogManager::getInstance();
			logData.setType("Warn");
			logData.setPId(common::Process::getPId());
			logData.setDateTime(common::DateTime::getTimeStampMicroString());

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_TAG_SIZE));
			logData.setTag(tag);

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_MSG_SIZE));
			logData.setMsg(msg);

			logManager->CreateLog(logData);
		}

		void Log::Info(std::string tag, std::string msg)
		{
			LogManager *logManager = LogManager::getInstance();
			logData.setType("Info");
			logData.setPId(common::Process::getPId());
			logData.setDateTime(common::DateTime::getTimeStampMicroString());

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_TAG_SIZE));
			logData.setTag(tag);

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_MSG_SIZE));
			logData.setMsg(msg);
		
			logManager->CreateLog(logData);
		}

		void Log::Debug(std::string tag, std::string msg)
		{
			LogManager *logManager = LogManager::getInstance();
			logData.setType("Debug");
			logData.setPId(common::Process::getPId());
			logData.setDateTime(common::DateTime::getTimeStampMicroString());

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_TAG_SIZE));
			logData.setTag(tag);

			if (tag.size() > MAX_LOG_TAG_SIZE)
				logData.setTag(tag.substr(0, MAX_LOG_MSG_SIZE));
			logData.setMsg(msg);

			logManager->CreateLog(logData);
		}
	} // namespace util
} // namespace gc

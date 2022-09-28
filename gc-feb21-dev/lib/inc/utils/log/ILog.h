/**
* @File ILog.h
* @Author Gaurav
* @Brief Base Interface for all Log types  
*
* Internal to the Log system.
* Contains virtual functions.
*/

#pragma once
#include <string>

#include "LogData.h"

namespace gc
{
	namespace util
	{
		struct ILog
		{
			virtual ~ILog();

			/**
			* @Brief Creates Log. To be implemented by all subclasses
			* @param LogData: Object of LogData containing data to be logged
			* @return bool : true if log successful, else flase .
			*/
			virtual bool CreateLog(LogData &logData) = 0;
		};

	} // namespace util
} // namespace gc

/**
* @Class ALog.h
* @Author Gaurav
* @Brief Abstraction for all Log Classes  
*
* Abstract class
* Implements ILog class
* Provides Implementation for CreateLog() method of ILog class.
* Internal to the Log system.
* Adds 
*/

#pragma once
#include "ILog.h"
#include "LogData.h"

namespace gc
{
	namespace util
	{
		class ALog : public ILog
		{
		protected:
			/**
			* pointer to ALog type to implement chain of responsibility
			*/
			ALog *successor;

			/**
			* to enable or disable current current log in case it fails 
			*/
			bool enabled;

			/**
			* @Brief Check if current log type is enabled
			* @return true if logging enabled for current log type, else flase .
			*/
			bool isEnabled();

			/**
			* @Brief set current log type enabled or disabled
			* @param true/false
			*/
			void setEnabled(bool enabled);

		public:
			/**
			* @Brief Parameterized constructor. Takes an ALog object pointer as agrument and creates the chain
			* for chain of responsibility design pattern
			* @param ALog * : Object poiner of ALog  
			*/
			ALog(ALog *);
			virtual ~ALog();

			/**
			* @Brief Return the next member in the chain
			* @return ALog * : Object of ALog
			*/
			ALog *getSuccessor();

			/**
			* @Brief Creates chain of responsibility. Calls SaveLog to actually create log 
			* @param LogData : Object of LogData containing data to be logged which is forwarded to SaveLog()
			* @return bool : true if log successful, else flase .
			*/
			bool CreateLog(LogData &logData); //do not override

			/**
			* @Brief Creates Log in respective location. To be implemented by all subclasses
			* @param LogData : Object of LogData containing data to be logged
			* @return bool : true if log successful, else flase.
			*/
			virtual bool SaveLog(LogData &logData) = 0;
		};
	} // namespace util
} // namespace gc

#include <iostream>

#include "ALog.h"

using namespace std;

namespace gc
{
	namespace util
	{
		ALog::ALog(ALog *successor) : successor(successor), enabled(true)
		{
		}

		ALog::~ALog()
		{
		}

		bool ALog::isEnabled()
		{
			return enabled;
		}

		void ALog::setEnabled(bool enabled)
		{
			this->enabled = enabled;
		}

		ALog *ALog::getSuccessor()
		{
			return successor;
		}

		bool ALog::CreateLog(LogData &logData)
		{
			bool state = true;
			if (true == enabled)
			{
				state = SaveLog(logData);
			}
			if (NULL != successor)
				state = state && successor->CreateLog(logData);

			return state;
		}

	} // namespace util
} // namespace gc

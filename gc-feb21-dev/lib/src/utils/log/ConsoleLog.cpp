#include <iostream>

#include "ConsoleLog.h"

#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"
#define MAKE_RED "\e[31m"

namespace gc
{
	namespace util
	{
		using namespace std;
		ConsoleLog::ConsoleLog(ALog *successor) : ALog(successor)
		{
		}

		ConsoleLog::~ConsoleLog()
		{
			cout << RESET_COLOR;
			this->successor = NULL;
		}

		bool ConsoleLog::SaveLog(LogData &logData)
		{
			cout << "\n";
			if (logData.getType() == "Error")
				cout << MAKE_RED;
			else if (logData.getType() == "Warn")
				cout << MAKE_GREEN;
			cout << logData.getType() << '/' << logData.getTag() << '\t' << logData.getDateTime() << '\t' << logData.getPId() << '\t' << logData.getMsg() << endl;
			cout << RESET_COLOR;

			return true;
		}

	} // namespace util
} // namespace gc

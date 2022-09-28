#include "LogFileException.h"

namespace gc
{
	namespace util
	{
		namespace log
		{
			LogFileException::LogFileException(const std::string &msg) : GCException(msg)
			{
			}
		} // namespace log

	} // namespace util
} // namespace gc

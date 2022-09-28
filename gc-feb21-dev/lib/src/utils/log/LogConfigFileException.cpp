#include "LogConfigFileException.h"

namespace gc
{
	namespace util
	{
		namespace log
		{
			LogConfigFileException::LogConfigFileException(const std::string &msg) : GCException(msg)
			{
			}
		} // namespace log

	} // namespace util
} // namespace gc

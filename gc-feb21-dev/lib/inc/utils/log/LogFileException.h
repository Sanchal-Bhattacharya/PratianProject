#pragma once
#include "GCException.h"

namespace gc
{
	namespace util
	{
		namespace log
		{
			class LogFileException : public GCException
			{
			public:
				LogFileException(const std::string &msg);
			};

		} // namespace log
	} // namespace util
} // namespace gc

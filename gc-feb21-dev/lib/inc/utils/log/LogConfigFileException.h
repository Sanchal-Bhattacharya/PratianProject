#pragma once
#include "GCException.h"

namespace gc
{
	namespace util
	{
		namespace log
		{
			class LogConfigFileException : public GCException
			{
			public:
				LogConfigFileException(const std::string &msg);
			};

		} // namespace log
	} // namespace util
} // namespace gc

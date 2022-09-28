#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBConfigFileException : public GCException
		{
		public:
			DBConfigFileException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

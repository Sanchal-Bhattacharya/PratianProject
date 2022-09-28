#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBConnectionException : public GCException
		{
		public:
			DBConnectionException(const std::string &msg);
		};
	} // namespace db
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBDataTableException : public GCException
		{
		public:
			DBDataTableException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

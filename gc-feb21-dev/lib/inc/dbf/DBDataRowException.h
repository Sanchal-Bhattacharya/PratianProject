#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBDataRowException : public GCException
		{
		public:
			DBDataRowException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBDataColumnException : public GCException
		{
		public:
			DBDataColumnException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

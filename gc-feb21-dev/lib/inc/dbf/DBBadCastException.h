#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBBadCastException : public GCException
		{
		public:
			DBBadCastException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

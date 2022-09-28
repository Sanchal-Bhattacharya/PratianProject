#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBObjectException : public GCException
		{
		public:
			DBObjectException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

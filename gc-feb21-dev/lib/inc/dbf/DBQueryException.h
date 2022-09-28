#pragma once
#include "GCException.h"

namespace gc
{
	namespace db
	{
		class DBQueryException : public GCException
		{
		public:
			DBQueryException(const std::string &msg);
		};
	} // namespace db
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace dao
	{
		class DAOQueryException : public GCException
		{
		public:
			DAOQueryException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

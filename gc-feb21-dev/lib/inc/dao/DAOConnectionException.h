#pragma once
#include "GCException.h"

namespace gc
{
	namespace dao
	{
		class DAOConnectionException : public GCException
		{
		public:
			DAOConnectionException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

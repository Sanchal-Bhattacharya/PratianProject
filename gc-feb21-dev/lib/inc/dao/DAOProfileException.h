#pragma once
#include "GCException.h"

namespace gc
{
	namespace dao
	{
		class DAOProfileException : public GCException
		{
		public:
			DAOProfileException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace dao
	{
		class DAOInstanceException : public GCException
		{
		public:
			DAOInstanceException(const std::string &msg);
		};
	} // namespace dao
} // namespace gc

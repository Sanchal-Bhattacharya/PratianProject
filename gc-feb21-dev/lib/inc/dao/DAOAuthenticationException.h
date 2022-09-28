#pragma once
#include "GCException.h"

namespace gc
{
	namespace dao
	{
		class DAOAuthenticationException : public GCException
		{
		public:
			DAOAuthenticationException(const std::string &msg);
		};

	} // namespace dao
} // namespace gc

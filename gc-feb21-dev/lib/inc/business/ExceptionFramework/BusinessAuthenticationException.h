#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class BusinessAuthenticationException : public GCException
		{
		public:
			BusinessAuthenticationException(const std::string &msg);
		};
	} // namespace business
} // namespace gc

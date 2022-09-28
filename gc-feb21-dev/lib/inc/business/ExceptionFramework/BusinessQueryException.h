#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class BusinessQueryException : public GCException
		{
		public:
			BusinessQueryException(const std::string &msg);
		};
	} // namespace business
} // namespace gc

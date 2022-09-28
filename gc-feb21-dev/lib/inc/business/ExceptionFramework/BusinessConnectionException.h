#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class BusinessConnectionException : public GCException
		{
		public:
			BusinessConnectionException(const std::string &msg);
		};
	} // namespace business
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class BusinessInstanceException : public GCException
		{
		public:
			BusinessInstanceException(const std::string &msg);
		};
	} // namespace business
} // namespace gc

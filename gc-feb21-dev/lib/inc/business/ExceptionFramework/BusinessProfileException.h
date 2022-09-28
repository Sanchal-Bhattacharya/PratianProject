#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class BusinessProfileException : public GCException
		{
		public:
			BusinessProfileException(const std::string &msg);
		};
	} // namespace business
} // namespace gc

#pragma once
#include "GCException.h"

namespace gc
{
	namespace business
	{
		class ConnectionIdNotFound : public GCException
		{
		public:
			ConnectionIdNotFound(const std::string &msg);
		};
	} // namespace business
} // namespace gc

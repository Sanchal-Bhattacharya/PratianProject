#pragma once
#include "GCException.h"

namespace gc
{
	namespace web
	{
		class WebConnectionException : public GCException
		{
		public:
			WebConnectionException(const std::string &msg);
		};
	} // namespace web
} // namespace gc

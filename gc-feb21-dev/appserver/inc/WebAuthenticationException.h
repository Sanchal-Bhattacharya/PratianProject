#pragma once
#include "GCException.h"

namespace gc
{
	namespace web
	{
		class WebAuthenticationException : public GCException
		{

		public:
			WebAuthenticationException(const std::string &msg);
		};

	} // namespace web
} // namespace gc

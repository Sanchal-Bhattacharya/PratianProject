#pragma once
#include "GCException.h"

namespace gc
{
	namespace web
	{
		class WebProfileException : public GCException
		{
		public:
			WebProfileException(const std::string &msg);
		};
	} // namespace web
} // namespace gc

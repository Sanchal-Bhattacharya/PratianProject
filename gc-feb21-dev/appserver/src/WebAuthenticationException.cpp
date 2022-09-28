#include "WebAuthenticationException.h"

namespace gc
{
	namespace web
	{
		WebAuthenticationException::WebAuthenticationException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace web
} // namespace gc

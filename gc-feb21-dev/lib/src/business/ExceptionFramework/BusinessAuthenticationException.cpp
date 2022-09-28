#include "BusinessAuthenticationException.h"

namespace gc
{
	namespace business
	{
		BusinessAuthenticationException::BusinessAuthenticationException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

#include "BusinessConnectionException.h"

namespace gc
{
	namespace business
	{
		BusinessConnectionException::BusinessConnectionException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

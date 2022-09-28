#include "ConnectionIdNotFound.h"

namespace gc
{
	namespace business
	{
		ConnectionIdNotFound::ConnectionIdNotFound(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

#include "BusinessQueryException.h"

namespace gc
{
	namespace business
	{
		BusinessQueryException::BusinessQueryException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

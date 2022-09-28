#include "BusinessProfileException.h"

namespace gc
{
	namespace business
	{
		BusinessProfileException::BusinessProfileException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

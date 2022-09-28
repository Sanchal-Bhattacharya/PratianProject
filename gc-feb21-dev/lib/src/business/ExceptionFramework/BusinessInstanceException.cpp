#include "BusinessInstanceException.h"

namespace gc
{
	namespace business
	{
		BusinessInstanceException::BusinessInstanceException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace business
} // namespace gc

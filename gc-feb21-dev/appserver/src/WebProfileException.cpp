#include "WebProfileException.h"

namespace gc
{
	namespace web
	{
		WebProfileException::WebProfileException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace web
} // namespace gc

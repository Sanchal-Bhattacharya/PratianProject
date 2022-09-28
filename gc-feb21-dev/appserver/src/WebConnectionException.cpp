#include "WebConnectionException.h"

namespace gc
{
	namespace web
	{
		WebConnectionException::WebConnectionException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace web
} // namespace gc

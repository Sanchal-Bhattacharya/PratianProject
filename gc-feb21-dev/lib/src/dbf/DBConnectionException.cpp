#include "DBConnectionException.h"

namespace gc
{
	namespace db
	{
		DBConnectionException::DBConnectionException(const std::string &msg) : GCException(msg)
		{
		}

	} // namespace db
} // namespace gc

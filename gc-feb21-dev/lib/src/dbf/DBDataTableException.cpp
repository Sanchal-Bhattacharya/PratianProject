#include "DBDataTableException.h"

namespace gc
{
	namespace db
	{
		DBDataTableException::DBDataTableException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace db
} // namespace gc

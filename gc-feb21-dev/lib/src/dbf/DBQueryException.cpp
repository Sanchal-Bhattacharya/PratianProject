#include "DBQueryException.h"

namespace gc
{
	namespace db
	{
		DBQueryException::DBQueryException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace db
} // namespace gc

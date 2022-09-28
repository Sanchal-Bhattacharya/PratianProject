#include "DBDataRowException.h"

namespace gc
{
	namespace db
	{
		DBDataRowException::DBDataRowException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

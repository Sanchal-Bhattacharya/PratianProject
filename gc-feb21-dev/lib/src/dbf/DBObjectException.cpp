#include "DBObjectException.h"

namespace gc
{
	namespace db
	{
		DBObjectException::DBObjectException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

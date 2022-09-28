#include "DBDataColumnException.h"

namespace gc
{
	namespace db
	{
		DBDataColumnException::DBDataColumnException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

#include "DBBadCastException.h"

namespace gc
{
	namespace db
	{
		DBBadCastException::DBBadCastException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace db
} // namespace gc

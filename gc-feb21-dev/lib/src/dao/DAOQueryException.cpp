#include "DAOQueryException.h"

namespace gc
{
	namespace dao
	{
		DAOQueryException::DAOQueryException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

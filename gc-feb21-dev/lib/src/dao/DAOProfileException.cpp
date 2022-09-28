#include "DAOProfileException.h"

namespace gc
{
	namespace dao
	{
		DAOProfileException::DAOProfileException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

#include "DAOConnectionException.h"

namespace gc
{
	namespace dao
	{
		DAOConnectionException::DAOConnectionException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

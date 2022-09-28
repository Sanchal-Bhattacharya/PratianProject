#include "DAOInstanceException.h"

namespace gc
{
	namespace dao
	{
		DAOInstanceException::DAOInstanceException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

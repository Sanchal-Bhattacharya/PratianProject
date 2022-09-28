#include "DAOAuthenticationException.h"

namespace gc
{
	namespace dao
	{
		DAOAuthenticationException::DAOAuthenticationException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace dao
} // namespace gc

#include "DBConfigFileException.h"

namespace gc
{
	namespace db
	{
		DBConfigFileException::DBConfigFileException(const std::string &msg) : GCException(msg)
		{
		}
	} // namespace db
} // namespace gc

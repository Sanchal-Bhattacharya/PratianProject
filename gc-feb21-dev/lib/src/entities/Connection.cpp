#include "Connection.h"
#include <string>

namespace gc
{
	namespace entities
	{
		Connection::Connection(int _cId, std::string _fromId, std::string _toId, int _isBlocked = 0)
		{
			cId = _cId;
			fromId = _fromId;
			toId = _toId;
			isBlocked = _isBlocked;
		}

		std::string Connection::getfromId()
		{
			return fromId;
		}

		std::string Connection::gettoId()
		{
			return toId;
		}

		int Connection::getcId()
		{
			return cId;
		}

		int Connection::getisBlocked()
		{
			return isBlocked;
		}

		void Connection::setisBlocked(int _isBlocked)
		{
			isBlocked = _isBlocked;
		}

	} // namespace entities
} // namespace gc

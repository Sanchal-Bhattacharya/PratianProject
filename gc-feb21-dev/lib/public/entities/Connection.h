#pragma once
#include <string>

namespace gc
{
	namespace entities
	{
		class Connection
		{
			int cId;
			std::string fromId;
			std::string toId;
			int isBlocked;

		public:
			Connection(int _cId, std::string _fromId, std::string _toId, int _isBlocked);

			std::string getfromId();

			std::string gettoId();

			int getcId();

			int getisBlocked();

			void setisBlocked(int _isBlocked);
		};
	} // namespace entities
} // namespace gc

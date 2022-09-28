#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"

namespace gc
{
	namespace common
	{
		class DateTime
		{
		public:
			static const std::string getTimeStampMicroString()
			{
				return boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::local_time());
			}
			static const std::string getTimeStampSecString()
			{
				return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
			}
		};

	} // namespace common
} // namespace gc

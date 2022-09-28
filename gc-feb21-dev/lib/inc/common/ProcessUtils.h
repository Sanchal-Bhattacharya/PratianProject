#pragma once
#include <sys/types.h>
#include <unistd.h>
namespace gc
{
	namespace common
	{
		class Process
		{
		public:
			static int getPId()
			{
				return getpid();
			}
		};
	} // namespace common
} // namespace gc

#pragma once
#include "IConnectionObserver.h"
#include "ConnectionObserver.h"
namespace gc
{
	namespace business
	{
		class ConnectionObserverFactory
		{
		public:
			static IConnectionObserver *getObserverInstance();
		};
	} // namespace business
} // namespace gc

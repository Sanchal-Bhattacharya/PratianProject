#include "ConnectionObserverFactory.h"

namespace gc
{
	namespace business
	{
		IConnectionObserver *ConnectionObserverFactory::getObserverInstance()
		{
			return ConnectionObserver::getObserverInstance();
		}
	} // namespace business
} // namespace gc

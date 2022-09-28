#pragma once

#include "IUserService.h"
#include "IMessageService.h"
#include "IGroupService.h"

namespace gc
{
	namespace business
	{
		class GcBusinessManager
		{
		public:
			static IUserService *getUserService();
			static IMessageService *getMessageService();
			static IGroupService *getGroupService();
		};
	} // namespace business
} // namespace gc

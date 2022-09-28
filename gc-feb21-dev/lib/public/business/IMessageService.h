#pragma once
#include <iostream>
#include <vector>

#include "Message.h"

namespace gc
{
	namespace business
	{
		struct IMessageService
		{
			virtual bool addMessage(entities::Message *messageVec) = 0;
			virtual std ::vector<entities::Message *> removeMessage(std::string userId) = 0;
			virtual bool addMessageToGroup(entities::Message *messagePtr) = 0;
			virtual std ::vector<entities::Message *> removeMessagesFromGroups(std::string userId) = 0;
			virtual ~IMessageService();
		};
	} // namespace business
} // namespace gc

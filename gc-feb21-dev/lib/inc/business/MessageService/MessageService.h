#pragma once
#include <string>
#include <vector>

#include "MQueueManager.h"
#include "Message.h"

#include "IMessageService.h"

using namespace std;

namespace gc
{
	namespace business
	{
		class MessageService : public IMessageService
		{
			MQueueManager *queueManager;
			static string LogTag;

		public:
			//static int counter;
			MessageService();

			bool addMessage(entities::Message *messagePtr);
			bool addMessageToGroup(entities::Message *messagePtr);
			vector<entities::Message *> removeMessage(string userId);
			vector<entities::Message *> removeMessagesFromGroups(string userId);
		};
		//int MessageManager :: counter = 0;
	} // namespace business
} // namespace gc

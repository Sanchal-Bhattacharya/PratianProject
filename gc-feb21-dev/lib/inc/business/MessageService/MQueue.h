#pragma once

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <vector>

#include "Message.h"
#include "MQueue.h"

using namespace std;

namespace gc
{
	namespace business
	{
		class MQueue
		{
			unsigned int QId;
			static const string& LogTag;
			static const unsigned int QueueCapacity = 1024;

			typedef boost::lockfree::spsc_queue<entities::Message *, boost::lockfree::capacity<QueueCapacity>> MESSAGE_QUEUE;

			std::string uId1;
			std::string uId2;
			MESSAGE_QUEUE msgQueue1; // input queue for userID1
			MESSAGE_QUEUE msgQueue2; // input queue for userID2

			bool pushTypeMessage(gc::entities::Message *message);
			bool pushTypeAck(gc::entities::Message *message);
			bool pushTypeMessageToGroup(gc::entities::Message *message);
			bool pushTypeAckFromGroup(gc::entities::Message *message);

		public:
			MQueue(const unsigned int QId, const std::string &uId1, const std::string &uId2);
			~MQueue();

			unsigned int getQId();

			bool pushMessage(entities::Message *message);
			vector<entities::Message *> popMessage(const string &userId);
		};
	} // namespace business
} // namespace gc

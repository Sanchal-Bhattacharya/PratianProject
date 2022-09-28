# pragma once

# include <map>
# include <string>
# include <vector>
# include "GroupConnectionCache.h"
# include "ConnectionCache.h"
# include "Message.h"
# include "MQueue.h"
# include "DAOManager.h"
# include "IGroupServiceDAO.h"
# include "IMessageServiceDAO.h"



using namespace std;

namespace gc
{
	namespace business
	{

		class MQueueManager
		{
			ConnectionCache * connCachePtr;
            GroupConnectionCache * groupConnectionCachePtr;
			static MQueueManager mQManagerInstance;
			static const char * LogTag ;
			map< unsigned int, MQueue * > mQMap;
            map< unsigned int, MQueue * > gQMap;
		    void restoreMessageQueues();	
			MQueue * createQueue(const unsigned int & QId, const string & uId1, const string & uId2 );

			MQueueManager();//######### check for singleton
			~MQueueManager();

				public:
			static MQueueManager * getMQueueManagerInstance();
			
			bool addMessages( entities::Message * messagePtr );
            bool addMessagesToGroup( entities :: Message * messagePtr);
			vector<entities::Message * > getMessages(std::string userId);
            vector<entities :: Message *> getMessagesFromGroups(std :: string userId);
            bool sendAck(entities :: Message * messagePtr);
		};
	}
}

#include "ConnectionObserver.h"
#include "GroupConnectionCache.h"

namespace gc
{
	namespace business
	{
		ConnectionObserver *ConnectionObserver::observer = nullptr;

		ConnectionObserver::ConnectionObserver()
		{
		}

		ConnectionObserver *ConnectionObserver::getObserverInstance()
		{
			if (observer == nullptr)
			{
				observer = new ConnectionObserver();
			}
			return observer;
		}

		void ConnectionObserver::notify(entities::User *user)
		{
			ConnectionCache::getConnectionCacheInstance()->addNewUserToList(user);
		}

		void ConnectionObserver::userDeleted(std::string email)
		{
			ConnectionCache::getConnectionCacheInstance()->deleteUserFromList(email);
		}

		void ConnectionObserver::onBlock(std::string user1, std::string user2)
		{
			ConnectionCache::getConnectionCacheInstance()->addUserConnection(user1, user2);
		}

		void ConnectionObserver::onUnblock(std::string user1, std::string user2)
		{
			ConnectionCache::getConnectionCacheInstance()->removeUserConnection(user1, user2);
		}

		void ConnectionObserver::newGroup(entities::Group *group)
		{
			std::string groupName = group->getName();
			GroupConnectionCache::getGroupConnectionCacheInstance()->addNewGroupToList(groupName);
		}

		void ConnectionObserver::updateGroup(std::string oldName, std::string newName)
		{
			GroupConnectionCache::getGroupConnectionCacheInstance()->updateGroupInCache(oldName, newName);
		}

		void ConnectionObserver::deleteGroup(std::string groupName)
		{
			GroupConnectionCache::getGroupConnectionCacheInstance()->deleteGroupFromCache(groupName);
		}

		void ConnectionObserver::newMember(std::string groupName, std::string email)
		{
			GroupConnectionCache::getGroupConnectionCacheInstance()->addNewUserToList(groupName, email);
		}

		void ConnectionObserver::removeMember(std::string groupName, std::string email)
		{
			GroupConnectionCache::getGroupConnectionCacheInstance()->removeUserFromList(groupName, email);
		}

		ConnectionObserver::~ConnectionObserver()
		{
			observer = nullptr;
		}
	} // namespace business
} // namespace gc

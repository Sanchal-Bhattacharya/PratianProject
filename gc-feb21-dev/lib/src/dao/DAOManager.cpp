#include "UserServiceDAO.h"
#include "MessageServiceDAO.h"
#include "GroupServiceDAO.h"
#include "DAOInstanceException.h"
#include "Log.h"

#include "DAOManager.h"

namespace gc
{
	namespace dao
	{
		IUserServiceDAO *DAOManager::getUserServiceDAO()
		{
			IUserServiceDAO *IU = new UserServiceDAO();
			if (NULL == IU)
			{
				util::Log::Error("DAOUserService", "UserService Instance Not Created");
				throw DAOInstanceException("UserService Instance Not Created");
			}
			util::Log::Info("DAOUserService", "UserService Instance Created");
			return IU;
		}
		IMessageServiceDAO *DAOManager::getMessageServiceDAO()
		{
			IMessageServiceDAO *IM = new MessageServiceDAO();
			if (NULL == IM)
			{
				util::Log::Error("DAOMessageService", "MessageService Instance Not Created");
				throw DAOInstanceException("MessageService Instance Not Created");
			}
			util::Log::Info("DAOMessageService", "MessageService Instance Created");
			return IM;
		}
		IGroupServiceDAO *DAOManager::getGroupServiceDAO()
		{
			IGroupServiceDAO *IG = new GroupServiceDAO();
			if (NULL == IG)
			{
				util::Log::Error("DAOGroupService", "GroupService Instance Not Created");
				throw DAOInstanceException("GroupService Instance Not Created");
			}
			util::Log::Info("DAOGroupService", "GroupService Instance Created");
			return IG;
		}
	} // namespace dao
} // namespace gc

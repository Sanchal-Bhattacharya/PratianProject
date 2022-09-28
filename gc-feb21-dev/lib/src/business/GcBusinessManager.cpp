#include <iostream>

#include "UserService.h"
#include "GroupService.h"
#include "MessageService.h"

#include "GcBusinessManager.h"
#include "BusinessInstanceException.h"
#include "Log.h"

namespace gc
{
	namespace business
	{
		IUserService* GcBusinessManager::getUserService()
		{
			IUserService* IU = new UserService();
			if(IU == nullptr)
			{
				util::Log::Error("GCBusinessManager","User service Instance not Created");
				throw BusinessInstanceException("User Service Instance Not Created");
			}
			util::Log::Info("GCBusinessManager","User service Instance successfully Created");
			return IU; 
		}

		IMessageService* GcBusinessManager::getMessageService()
		{
			IMessageService* IM = new MessageService();
			if(IM == nullptr)
			{
				util::Log::Error("GCBusinessManager","Message service Instance not Created");
				throw BusinessInstanceException("Message Service Instance Not Created");
			}
			util::Log::Info("GCBusinessManager","Message service Instance successfully Created");
			return IM;
		}

		IGroupService* GcBusinessManager::getGroupService()
		{
            IGroupService* IG = new GroupService();
			if(IG == nullptr)
			{
				util::Log::Error("GCBusinessManager","Group service Instance not Created");
				throw BusinessInstanceException("Group Service Instance Not Created");
			}
			util::Log::Info("GCBusinessManager","Group service Instance successfully Created");
			return IG;
		} 
	}
}			
		

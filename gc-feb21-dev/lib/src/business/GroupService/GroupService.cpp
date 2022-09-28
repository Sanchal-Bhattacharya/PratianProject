#include "IGroupServiceDAO.h"
#include "DAOManager.h"
#include "ConnectionObserverFactory.h"
#include "DAOConnectionException.h"
#include "BusinessQueryException.h"
#include "DAOQueryException.h"
#include "BusinessConnectionException.h"
#include "Log.h"

#include "GroupService.h"

namespace gc
{
	namespace business
	{
		GroupService::GroupService()
		{
		}

		void GroupService::createGroup(entities::Group *group)
		{
			// Yet to be Created:   entities :: Group
			//                      IGroupService
			//                      dao::DAOManager::getGroupServiceDAO();
			//
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				IG->createGroup(group);
				util::Log::Info("Group Service", "Adding Group to Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->newGroup(group);
				util::Log::Info("Group Service", "Group service Instance successfully Created and Group created into the system");
				delete IG;
				IG = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::createGroup()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::createGroup()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::createGroup()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::createGroup()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		void GroupService::deleteGroup(std::string groupName)
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				IG->deleteGroup(groupName);
				util::Log::Info("Group Service", "Group service Instance successfully Created and Group deleted from the system");
				delete IG;
				IG = nullptr;
				util::Log::Info("Group Service", "Removing Group from Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->deleteGroup(groupName);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::deleteGroup()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::deleteGroup()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::deleteGroup()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::deleteGroup()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		void GroupService::updateGroup(std::string oldName, std::string newName)
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				IG->updateGroup(oldName, newName);
				util::Log::Info("Group Service", "Group service Instance successfully Created and Group updated into the system");
				delete IG;
				IG = nullptr;
				util::Log::Info("Group Service", "Updating the groupconnectioncache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->updateGroup(oldName, newName);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::updateGroup()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::updateGroup()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::updateGroup()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::updateGroup()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		void GroupService::addMember(std::string groupName, std::string email)
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				IG->addMember(groupName, email);
				util::Log::Info("Group Service", "Group service Instance successfully Created and user added to the group");
				delete IG;
				IG = nullptr;
				util::Log::Info("Group Service", "Addding member to Group in Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->newMember(groupName, email);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::AddUser()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::AddUser()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::AddUser()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::AddUser()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}
		void GroupService::removeMember(std::string groupName, std::string email)
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				IG->removeUser(groupName, email);
				util::Log::Info("Group Service", "Group service Instance successfully Created and user removed from the group");
				delete IG;
				IG = nullptr;
				util::Log::Info("Group Service", "Removing Member from Group in Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->removeMember(groupName, email);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::removeUser()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::removeUser()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::removeUser()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCRemoveService::removeUser()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		std::vector<std::string> GroupService::getUsers(std::string groupName)
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				util::Log::Info("Group Service", "Group service Instance successfully Created");
				std::vector<std::string> userList = IG->getAllUsers(groupName);
				util::Log::Info("Group Service", "Group user details retreived and to be returned from system");
				delete IG;
				IG = nullptr;
				return userList;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::getUsers()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::getUsers()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::getUsers()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::getUsers()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		std::vector<std::string> GroupService::getAllGroups()
		{
			dao::IGroupServiceDAO *IG;
			try
			{
				IG = dao::DAOManager::getGroupServiceDAO();
				util::Log::Info("Group Service", "Group service Instance successfully Created");
				std::vector<std::string> groups = IG->getAllGroups();
				util::Log::Info("Group Service", "Group details list returned from system");
				delete IG;
				IG = nullptr;
				return groups;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCGroupService::getAllGroups()", dqe.what());
				delete IG;
				IG = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCGroupService::getAllGroups()", dce.what());
				delete IG;
				IG = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCGroupService::getAllGroups()", gc.what());
				delete IG;
				IG = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCGroupService::getAllGroups()", "Unexpected Exception");
				delete IG;
				IG = nullptr;
				throw;
			}
		}

		GroupService::~GroupService()
		{
		}
	} // namespace business
} // namespace gc

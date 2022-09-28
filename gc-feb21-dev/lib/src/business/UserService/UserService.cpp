#include "DAOConnectionException.h"
#include "BusinessQueryException.h"
#include "DAOQueryException.h"
#include "BusinessConnectionException.h"
#include "DAOManager.h"
#include "IConnectionObserver.h"
#include "ConnectionObserverFactory.h"
#include "IUserServiceDAO.h"
#include "Log.h"

#include "UserService.h"

namespace gc
{
	namespace business
	{
		UserService::UserService()
		{
		}
		void UserService::createUser(entities::User *user)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				IU->createUser(user);
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->notify(user);
				util::Log::Info("User Service", "User service Instance successfully Created and user created into the system");
				delete IU;
				IU = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::CreateUser()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::CreateUser()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::CreateUser()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::CreateUser()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		void UserService::createUserFromList(std::vector<entities::User *> userlist)
		{
			dao::IUserServiceDAO *IU = dao::DAOManager::getUserServiceDAO();
			IU->createUserFromList(userlist);
			delete IU;
			IU = nullptr;
		}
		void UserService::updateUser(entities::User *user)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				IU->updateUser(user);
				util::Log::Info("User Service", "User service Instance successfully Created and user updated into the system");
				delete IU;
				IU = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::updateUser()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::updateUser()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::updateUser()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::updateUser()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		void UserService::deleteUser(std::string email)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				IU->deleteUser(email);
				util::Log::Info("User Service", "User service Instance successfully Created and user deleted from the system");
				delete IU;
				IU = nullptr;
				util::Log::Info("User Service", "Removing the user from Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->userDeleted(email);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::deleteUser()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::deleteUser()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::deleteUser()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::deleteUser()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}

		entities::User *UserService::getUser(std::string email)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				util::Log::Info("User Service", "User service Instance successfully Created");
				entities::User *iu = IU->getUser(email);
				util::Log::Info("User Service", "User details retreived and to be returned from system");
				delete IU;
				IU = nullptr;
				return iu;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::getUser()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::getUser()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::getUser()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::getUser()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		std::vector<entities::User *> UserService::getAllUsers()
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				util::Log::Info("User Service", "User service Instance successfully Created");
				std::vector<entities::User *> iu = IU->getAllUsers();
				util::Log::Info("User Service", "User details list returned from system");
				delete IU;
				IU = nullptr;
				return iu;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::getAllUsers()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::getAllUsers()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::getAllUsers()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::getAllUsers()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		void UserService::blockConnection(std::string email1, std::string email2)
		{

			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				if (IU->isBlocked(email1, email2))
					return;
				IU->blockconnection(email1, email2);
				util::Log::Info("User Service", "User service Instance successfully Created and user blocked");
				delete IU;
				IU = nullptr;
				util::Log::Info("User Service", "Removing the connection from Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->onBlock(email1, email2);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService:blockConnection()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::blockConnection()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::blockConnection()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::blockConnection()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		void UserService::unblockConnection(std::string email1, std::string email2)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				if (!IU->isBlocked(email1, email2))
					return;
				IU->unblockconnection(email1, email2);
				util::Log::Info("User Service", "User service Instance successfully Created and user unblocked from the system");
				delete IU;
				IU = nullptr;
				util::Log::Info("User Service", "Adding the connection to Connection Cache");
				IConnectionObserver *observer = ConnectionObserverFactory::getObserverInstance();
				observer->onUnblock(email1, email2);
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::unblockConnection()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::unblockConnection()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::unblockConnection()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::unblockConnection()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}

		bool UserService::isBlocked(std::string email1, std::string email2)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				IU->isBlocked(email1, email2);
				util::Log::Info("User Service", "User service Instance successfully Created and user unblocked from the system");
				delete IU;
				IU = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::isBlockeD()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::isBlocked()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::isBlocked()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::isBlocked()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}

		std::pair<std::string, std::string> UserService::login(std::string email)
		{
			dao::IUserServiceDAO *IU;
			try
			{
				IU = dao::DAOManager::getUserServiceDAO();
				util::Log::Info("User Service", "User service Instance successfully Created");
				std::pair<std::string, std::string> iu = IU->login(email);
				util::Log::Info("User Service", "Password & Salt pair returned successfully");
				delete IU;
				IU = nullptr;
				return iu;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Error("GCUserService::login()", dqe.what());
				delete IU;
				IU = nullptr;
				throw BusinessQueryException(dqe.what());
			}
			catch (dao::DAOConnectionException &dce)
			{
				util::Log::Error("GCUserService::login()", dce.what());
				delete IU;
				IU = nullptr;
				throw BusinessConnectionException(dce.what());
			}
			catch (GCException &gc)
			{
				util::Log::Error("GCUserService::login()", gc.what());
				delete IU;
				IU = nullptr;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GCUserService::login()", "Unexpected Exception");
				delete IU;
				IU = nullptr;
				throw;
			}
		}
		UserService::~UserService()
		{
		}
	} // namespace business
} // namespace gc

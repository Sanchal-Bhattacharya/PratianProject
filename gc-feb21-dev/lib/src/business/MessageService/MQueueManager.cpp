#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>

#include "ConnectionIdNotFound.h"
#include "MQueueManager.h"
#include "Log.h"
#include "DAOQueryException.h"

namespace gc
{
	namespace business
	{
		MQueueManager MQueueManager::mQManagerInstance;

		const char *MQueueManager::LogTag = "MessageService";

		MQueueManager *MQueueManager::getMQueueManagerInstance()
		{
			return &mQManagerInstance;
		}

		MQueueManager::MQueueManager()
		{
			connCachePtr = ConnectionCache::getConnectionCacheInstance();
			groupConnectionCachePtr = GroupConnectionCache::getGroupConnectionCacheInstance();
			try
			{
				restoreMessageQueues();
			}
			catch (ConnectionIdNotFound E)
			{
				util ::Log ::Error("RESTORE", E.what());
			}
			catch (...)
			{
				util ::Log ::Error("RESTORE", "UNKNOWN ERROR");
			}
		}

		MQueueManager::~MQueueManager()
		{
			map<unsigned int, MQueue *>::iterator mQIter = mQMap.begin();
			while (mQMap.end() != mQIter)
			{
				delete mQIter->second;
				mQIter->second = NULL;
				mQIter++;
			}
		}

		MQueue *MQueueManager::createQueue(const unsigned int &QId, const string &uId1, const string &uId2)
		{
			return new MQueue(QId, uId1, uId2);
		}

		bool MQueueManager::addMessages(entities::Message *messagePtr)
		{
			map<unsigned int, MQueue *>::iterator mQIter;
			unsigned int qId = -1;

			try
			{
				//will throw if connection not found in cache
				qId = connCachePtr->getConnectionId(messagePtr->getToId(), messagePtr->getFromId());
				mQIter = mQMap.find(qId);

				//queue doesn't already exist in queue list
				if (mQIter == mQMap.end())
				{
					MQueue *t_mQPtr = createQueue(qId, messagePtr->getToId(), messagePtr->getFromId());

					//if memory allocation for queue fails
					if (NULL == t_mQPtr)
					{
					}

					pair<map<unsigned int, MQueue *>::iterator, bool> qInsertStatus;
					qInsertStatus = mQMap.insert(std::make_pair<unsigned int, MQueue *>(std::forward<unsigned int>(qId), std::forward<MQueue *>(t_mQPtr)));

					if (false == qInsertStatus.second) //insert to message queue map fails
					{
						util::Log::Info(LogTag, "<MQueueManager>:failed to insert queue to map ");
						return false;
					}

					mQIter = mQMap.find(qId);
				}
			}
			catch (ConnectionIdNotFound E)
			{
				util::Log::Info(LogTag, "<MQueueManager>:Either User does not exist or user has been blocked");
				throw;
			}
			catch (...) //###################### edit to catch exception
			{
			}
			mQIter->second->pushMessage(messagePtr);

			return true;
		}

		bool MQueueManager::addMessagesToGroup(entities::Message *messagePtr)
		{
			map<unsigned int, MQueue *>::iterator gQIter;
			unsigned int qId = -1;
			try
			{
				//will throw if connection not found in cache
				std ::vector<std ::string> group_sender;
				const std ::string str = messagePtr->getFromId();
				boost::split(group_sender, str, boost::is_any_of(":"));
				qId = groupConnectionCachePtr->getConnectionId(group_sender[0], messagePtr->getToId());
				gQIter = gQMap.find(qId);
				//queue doesn't already exist in queue list
				if (gQIter == gQMap.end())
				{
					MQueue *t_mQPtr = createQueue(qId, messagePtr->getToId(), group_sender[0]);
					//if memory allocation for queue fails
					if (nullptr == t_mQPtr)
					{
					}

					pair<map<unsigned int, MQueue *>::iterator, bool> qInsertStatus;
					qInsertStatus = gQMap.insert(std::make_pair<unsigned int, MQueue *>(std::forward<unsigned int>(qId), std::forward<MQueue *>(t_mQPtr)));
					if (false == qInsertStatus.second) //insert to message queue map fails
					{
						util::Log::Info(LogTag, "<MQueueManager>:failed to insert queue to gmap ");
						return false;
					}
					gQIter = gQMap.find(qId);
				}
			}
			catch (ConnectionIdNotFound E)
			{
				util::Log::Info(LogTag, "<MQueueManager>:Group-User connection not found");
				throw;
			}
			catch (...) //###################### edit to catch exception
			{
			}
			gQIter->second->pushMessage(messagePtr);
			return true;
		}

		vector<entities::Message *> MQueueManager::getMessages(string userId)
		{
			vector<entities::Message *> messageVec, tempMessageVec;
			entities::Message *tempMsg = NULL;
			try
			{
				vector<unsigned int> qIdList = connCachePtr->getConnectionIdList(userId);

				vector<unsigned int>::iterator qIdIter = qIdList.begin();

				while (qIdList.end() != qIdIter)
				{
					map<unsigned int, MQueue *>::iterator mQIter;
					mQIter = mQMap.find(*qIdIter);

					if (mQIter != mQMap.end())
					{

						tempMessageVec = mQIter->second->popMessage(userId);
						vector<entities::Message *>::iterator tempIter = tempMessageVec.begin();

						while (tempMessageVec.end() != tempIter)
						{
							messageVec.push_back(*tempIter);
							tempIter++;
						}
					}
					qIdIter++;
				}

				util::Log::Info(LogTag, "<MQueueManager>:removed messages:" +
											boost::lexical_cast<string>(messageVec.size()));
				tempMsg = NULL;
			}

			catch (ConnectionIdNotFound E)
			{
				util::Log::Info(LogTag, "<MQueueManager>:Either User does not exist or user has been blocked");
				throw;
			}
			catch (...) //###################### edit to catch exception
			{
			}

			return messageVec;
		}

		vector<entities::Message *> MQueueManager::getMessagesFromGroups(string userId)
		{
			vector<entities::Message *> messageVec, tempMessageVec;
			entities::Message *tempMsg = NULL;
			try
			{
				vector<unsigned int> qIdList = groupConnectionCachePtr->getConnectionIdList(userId);

				vector<unsigned int>::iterator qIdIter = qIdList.begin();
				while (qIdList.end() != qIdIter)
				{

					map<unsigned int, MQueue *>::iterator gQIter;
					gQIter = gQMap.find(*qIdIter);

					if (gQIter != gQMap.end())
					{

						tempMessageVec = gQIter->second->popMessage(userId);
						vector<entities::Message *>::iterator tempIter = tempMessageVec.begin();

						while (tempMessageVec.end() != tempIter)
						{
							messageVec.push_back(*tempIter);
							tempIter++;
						}
					}
					qIdIter++;
				}

				util::Log::Info(LogTag, "<MQueueManager>:removed group messages:" +
											boost::lexical_cast<string>(messageVec.size()));
				tempMsg = NULL;
			}

			catch (ConnectionIdNotFound E)
			{
				util::Log::Info(LogTag, "<MQueueManager>:Either User does not exist or user has been blocked");
				throw;
			}
			catch (...) //###################### edit to catch exception
			{
			}

			return messageVec;
		}

		bool MQueueManager ::sendAck(entities ::Message *messagePtr)
		{
			map<unsigned int, MQueue *>::iterator gQIter;
			unsigned int qId = -1;
			try
			{
				//will throw if connection not found in cache
				std ::vector<std ::string> group_receiver;
				const std ::string str = messagePtr->getFromId();
				boost::split(group_receiver, str, boost::is_any_of(":"));
				qId = groupConnectionCachePtr->getConnectionId(group_receiver[0], messagePtr->getToId());

				gQIter = gQMap.find(qId);
				//queue doesn't already exist in queue list
				if (gQIter == gQMap.end())
				{
					MQueue *t_mQPtr = createQueue(qId, group_receiver[0], messagePtr->getToId());
					//if memory allocation for queue fails
					if (NULL == t_mQPtr)
					{
					}

					pair<map<unsigned int, MQueue *>::iterator, bool> qInsertStatus;
					qInsertStatus = gQMap.insert(std::make_pair<unsigned int, MQueue *>(std::forward<unsigned int>(qId), std::forward<MQueue *>(t_mQPtr)));
					if (false == qInsertStatus.second) //insert to message queue map fails
					{
						util::Log::Info(LogTag, "<MQueueManager>:failed to insert queue to gmap ");
						return false;
					}
					gQIter = gQMap.find(qId);
				}
			}
			catch (ConnectionIdNotFound E)
			{
				util::Log::Info(LogTag, "<MQueueManager>:Group-User connection not found");
				throw;
			}
			catch (...) //###################### edit to catch exception
			{
			}

			gQIter->second->pushMessage(messagePtr);
			return true;
		}
		void MQueueManager ::restoreMessageQueues()
		{
			dao::IMessageServiceDAO *IM;
			IM = dao::DAOManager::getMessageServiceDAO();
			try
			{
				std::vector<entities::Message *> restoreMessage = IM->restore();
				util ::Log ::Info(LogTag, "All previous messages from database restored to queues");
				if (!restoreMessage.empty())
				{
					std::vector<entities::Message *>::iterator restoreMIter = restoreMessage.begin();

					while (restoreMIter != restoreMessage.end())
					{
						const std::string fromID = (*restoreMIter)->getFromId();
						if (boost::algorithm::contains(fromID, ":"))
						{
							addMessagesToGroup(*restoreMIter);
						}
						else
						{
							addMessages(*restoreMIter);
						}
						++restoreMIter;
					}
				}
				delete IM;
				IM = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Info("Restoring Connection Cache", "Persistence Table is empty, so DAOQuerryException is thrown");
				delete IM;
				IM = nullptr;
			}
		}
	} // namespace business
} // namespace gc

#include <iostream>

#include <boost/algorithm/string.hpp>

#include "ConnectionIdNotFound.h"
#include "MessageService.h"
#include "MsgMacro.h"
#include "DAOManager.h"
#include "IGroupServiceDAO.h"
#include "IMessageServiceDAO.h"
#include "Log.h"

using namespace std;

namespace gc
{
    namespace business
    {
        string MessageService::LogTag {"MessageService"};

        MessageService::MessageService()
            : queueManager(MQueueManager::getMQueueManagerInstance())
        {
        }

        bool MessageService::addMessage(entities::Message *messagePtr)
        {
            try
            {
                if (NULL != messagePtr)
                {
                    queueManager->addMessages(messagePtr);
                    dao::IMessageServiceDAO *IM;
                    IM = dao::DAOManager::getMessageServiceDAO();
                    IM->addMessageDB(messagePtr);
                    delete IM;
                    IM = nullptr;
                }
            }
            catch (ConnectionIdNotFound E)
            {
                util::Log::Info(LogTag, "<MessageManager>:User not found");
                throw;
            }
            return true;
        }

        bool MessageService::addMessageToGroup(entities::Message *messagePtr)
        {
            try
            {
                if (NULL != messagePtr)
                {

                    dao::IGroupServiceDAO *IG;
                    try
                    {
                        IG = dao::DAOManager::getGroupServiceDAO();
                        // messagePtr->getToId() returns ID of the group
                        std ::vector<std ::string> GroupMembers = IG->getAllUsers(messagePtr->getToId());
                        std ::string email;
                        dao::IMessageServiceDAO *IM;
                        IM = dao::DAOManager::getMessageServiceDAO();
                        for (int i = 0; i < GroupMembers.size(); i++)
                        {
                            email = GroupMembers[i];
                            if (email != messagePtr->getFromId())
                            {
                                entities ::Message *message = new entities ::Message(messagePtr->getMsgId(), email, messagePtr->getToId() + ":" + messagePtr->getFromId(), messagePtr->getMessage(), messagePtr->getMessageType(), messagePtr->getAckStatus());
                                queueManager->addMessagesToGroup(message);
                                IM->addMessageDB(message);

                                queueManager->sendAck(new entities::Message(messagePtr->getMsgId(), messagePtr->getFromId(), messagePtr->getToId() + ":" + email, "", TYPE_ACK, ACK1));
                            }
                        }
                        util::Log::Info("Group Service", "Messages successfully added");
                        delete IG;
                        IG = nullptr;
                        delete IM;
                        IM = nullptr;
                    }
                    catch (...)
                    {
                        util::Log::Error("GCGroupService::addMessagesToGroup()", "Unexpected Exception");
                        delete IG;
                        IG = nullptr;
                        throw;
                    }
                }
            }
            catch (ConnectionIdNotFound E)
            {
                util::Log::Info(LogTag, "<MessageManager>:DAOExtraException not found");
                throw;
            }
            return true;
        }

        vector<entities::Message *> MessageService::removeMessage(string userId)
        {
            vector<entities::Message *> messageVec;
            try
            {
                messageVec = queueManager->getMessages(userId);
            }
            catch (ConnectionIdNotFound E)
            {
                util::Log::Info(LogTag, "<MessageManager>:User not found");
                throw;
            }
            dao::IMessageServiceDAO *IM;
            IM = dao::DAOManager::getMessageServiceDAO();
            std::vector<entities::Message *>::iterator MsgIter = messageVec.begin();
            while (MsgIter != messageVec.end())
            {
                IM->deleteMessageDB(*MsgIter);
                ++MsgIter;
            }
            delete IM;
            IM = nullptr;

            return messageVec;
        }

        vector<entities::Message *> MessageService::removeMessagesFromGroups(string userId)
        {
            vector<entities::Message *> messageVec;
            try
            {
                messageVec = queueManager->getMessagesFromGroups(userId);
                for (int i = 0; i < messageVec.size(); i++)
                {
                    std ::vector<std ::string> group_sender;
                    const std ::string str = messageVec[i]->getFromId();
                    boost::split(group_sender, str, boost::is_any_of(":"));
                    if (messageVec[i]->getAckStatus() != ACK2)
                    {
                        queueManager->sendAck(new entities::Message(messageVec[i]->getMsgId(), group_sender[1], group_sender[0] + ":" + userId, "", TYPE_ACK, ACK2));
                    }
                }
            }
            catch (ConnectionIdNotFound E)
            {
                util::Log::Info(LogTag, "<MessageManager>:groupId not found");
                throw;
            }

            dao::IMessageServiceDAO *IM;
            IM = dao::DAOManager::getMessageServiceDAO();

            std::vector<entities::Message *>::iterator MsgIter = messageVec.begin();

            while (MsgIter != messageVec.end())
            {
                IM->deleteMessageDB(*MsgIter);
                ++MsgIter;
            }
            delete IM;
            IM = nullptr;
            return messageVec;
        }
    } // namespace business
} // namespace gc

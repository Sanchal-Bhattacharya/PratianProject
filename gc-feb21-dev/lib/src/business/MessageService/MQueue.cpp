#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "MQueue.h"
#include "Log.h"
#include "MsgMacro.h"

using namespace std;

namespace gc
{
    namespace business
    {
        const string& MQueue::LogTag {"MessageService"};

        MQueue::MQueue(const unsigned int QId, const std::string &uId1, const std::string &uId2)
            : QId(QId), uId1(uId1), uId2(uId2)
        {
        }

        MQueue::~MQueue()
        {
            entities::Message *mPtr = NULL;

            while (msgQueue1.read_available() > 0)
            {
                mPtr = msgQueue1.front();
                msgQueue1.pop();
                delete mPtr;
            }

            while (msgQueue2.read_available() > 0)
            {
                mPtr = msgQueue2.front();
                msgQueue2.pop();
                delete mPtr;
            }
            mPtr = NULL;
            //#######do something to manage message objects(deallocation)
        }

        unsigned int MQueue::getQId()
        {
            return this->QId;
        }

        bool MQueue::pushTypeMessage(gc::entities::Message *message)
        {
            if (message->getToId() == uId1)
            {
                msgQueue1.push(message);
                msgQueue2.push(new entities::Message(message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1));
            }
            else if (message->getToId() == uId2)
            {
                msgQueue2.push(message);
                msgQueue1.push(new entities::Message(message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1));
            }
            else
            {
                util::Log::Info(LogTag, "<MQueue>Push Failed:couldn\'t match user");
                return false;
            }

            return true;
        }

        bool MQueue::pushTypeMessageToGroup(gc::entities::Message *message)
        {
            if (message->getToId() == uId1)
            {
                msgQueue1.push(message);
                //msgQueue2.push( new entities::Message( message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1 ) );
            }
            else if (message->getToId() == uId2)
            {
                msgQueue2.push(message);
                //msgQueue1.push( new entities::Message( message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1 ) );
            }
            else
            {
                util::Log::Info(LogTag, "<MQueue>Push Failed:couldn\'t match user");
                return false;
            }

            return true;
        }

        bool MQueue::pushTypeAck(entities::Message *message)
        {
            if (ACK3 == message->getAckStatus())
            {
                MESSAGE_QUEUE *mQPtr = NULL;
                if (message->getFromId() == uId1 && msgQueue1.read_available() > 0)
                {
                    mQPtr = &msgQueue1;
                }
                else if (message->getFromId() == uId2 && msgQueue2.read_available() > 0)
                {
                    mQPtr = &msgQueue2;
                }

                if (mQPtr->front()->getMsgId() == message->getMsgId())
                {
                    entities::Message *msgPtr = mQPtr->front();
                    mQPtr->pop();
                    delete msgPtr;
                    msgPtr = NULL;
                }

                mQPtr = NULL;
                delete message;
                message = NULL;
            }
            else
            {
                // invalid acknowledgment( ack other than ACK3 cannot be received )
            }
            return true;
        }

        bool MQueue::pushTypeAckFromGroup(entities::Message *message)
        {
            if (ACK1 == message->getAckStatus() || ACK2 == message->getAckStatus())
            {
                if (message->getToId() == uId1)
                {
                    msgQueue1.push(message);
                    //msgQueue2.push( new entities::Message( message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1 ) );
                }
                else if (message->getToId() == uId2)
                {
                    msgQueue2.push(message);
                    //msgQueue1.push( new entities::Message( message->getMsgId(), message->getFromId(), message->getToId(), "", TYPE_ACK, ACK1 ) );
                }
                else
                {
                    util::Log::Info(LogTag, "<MQueue>Push Failed:couldn\'t match user");
                    return false;
                }
            }
            else if (ACK3 == message->getAckStatus())
            {
                MESSAGE_QUEUE *mQPtr = NULL;
                if (message->getFromId() == uId1 && msgQueue1.read_available() > 0)
                {
                    mQPtr = &msgQueue1;
                }
                else if (message->getFromId() == uId2 && msgQueue2.read_available() > 0)
                {
                    mQPtr = &msgQueue2;
                }

                if (mQPtr->front()->getMsgId() == message->getMsgId())
                {
                    entities::Message *msgPtr = mQPtr->front();
                    mQPtr->pop();
                    delete msgPtr;
                    msgPtr = NULL;
                }

                mQPtr = NULL;
                delete message;
                message = NULL;
            }
            else
            {
                // invalid acknowledgment( ack other than ACK3 cannot be received )
            }
            return true;
        }

        // 				public methods
        bool MQueue::pushMessage(gc::entities::Message *message)
        {
            if (NULL == message)
            {
                return false;
            }

            // check if its a group message or not

            vector<std ::string> senders;
            const std ::string str = message->getFromId();
            boost::split(senders, str, boost::is_any_of(":"));

            if (senders.size() == 2)
            {
                if (TYPE_MSG == message->getMessageType())
                {
                    pushTypeMessageToGroup(message);
                }

                else if (TYPE_ACK == message->getMessageType())
                {
                    pushTypeAckFromGroup(message);
                }
                else
                {
                    // invalid type of message
                }
            }
            else
            {

                if (TYPE_MSG == message->getMessageType())
                {
                    pushTypeMessage(message);
                }

                else if (TYPE_ACK == message->getMessageType())
                {
                    pushTypeAck(message);
                }
                else
                {
                    // invalid type of message
                }
            }
            util::Log::Info(LogTag, "<MQueue>:" + boost::lexical_cast<string>(QId) + " Q1 : " +
                                        boost::lexical_cast<string>(msgQueue1.read_available()) + ":" +
                                        boost::lexical_cast<string>(msgQueue1.write_available()) + "\tQ2 " +
                                        boost::lexical_cast<string>(msgQueue2.read_available()) + ":" +
                                        boost::lexical_cast<string>(msgQueue2.write_available()));

            return true;
        }

        vector<entities::Message *> MQueue::popMessage(const string &userId)
        {
            vector<entities::Message *> messageVec;
            entities::Message *mPtr = NULL;
            MESSAGE_QUEUE *qPtrTo = NULL, *qPtrFrom = NULL;

            if (uId1 == userId)
            {
                qPtrFrom = &msgQueue1;
                qPtrTo = &msgQueue2;
            }
            else if (uId2 == userId)
            {
                qPtrFrom = &msgQueue2;
                qPtrTo = &msgQueue1;
            }

            while (qPtrFrom->read_available() > 0)
            {
                mPtr = qPtrFrom->front();
                qPtrFrom->pop();
                messageVec.push_back(mPtr);

                // push acknowlegdment
                if (TYPE_MSG == mPtr->getMessageType())
                {
                    vector<std ::string> senders;
                    const std ::string str = mPtr->getFromId();
                    boost::split(senders, str, boost::is_any_of(":"));
                    if (senders.size() == 1)
                    {
                        qPtrTo->push(new entities::Message(mPtr->getMsgId(), mPtr->getFromId(), mPtr->getToId(), "", TYPE_ACK, ACK2));
                    }
                }
            }

            vector<entities::Message *>::iterator tempIter = messageVec.begin();

            /*while( messageVec.end() != tempIter )
            {
                if( TYPE_MSG == (*tempIter)->getMessageType() ) 
                    qPtrFrom->push( new entities::Message( **tempIter ) );
                tempIter++;
            }*/

            util::Log::Info(LogTag, "<MQueue>:" + boost::lexical_cast<string>(QId) + " Q1 : " +
                                        boost::lexical_cast<string>(msgQueue1.read_available()) + ":" +
                                        boost::lexical_cast<string>(msgQueue1.write_available()) + "\tQ2 " +
                                        boost::lexical_cast<string>(msgQueue2.read_available()) + ":" +
                                        boost::lexical_cast<string>(msgQueue2.write_available()));

            return messageVec;
        }

    } // namespace business
} // namespace gc

#include "Message.h"

namespace gc
{
	namespace entities
	{
		Message::Message(int _msgId, std::string _toId, std::string _fromId, std::string _message, int _messageType, int _ackStatus)
			: msgId(_msgId), toId(_toId), fromId(_fromId), message(_message), messageType(_messageType), ackStatus(_ackStatus)
		{
		}

		std::string Message::getToId() const
		{
			return toId;
		}

		std::string Message::getFromId() const
		{
			return fromId;
		}

		int Message::getMsgId() const
		{
			return msgId;
		}

		std::string Message::getMessage() const
		{
			return message;
		}

		int Message::getAckStatus() const
		{
			if (messageType != 1)
				return -1;
			else
				return ackStatus;
		}

		int Message::getMessageType() const
		{
			return messageType;
		}
	} // namespace entities
} // namespace gc

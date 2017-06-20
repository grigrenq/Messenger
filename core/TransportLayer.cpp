#include <cstring>
#include "TransportLayer.hpp"

void TransportLayer::processMessage(char* msg)
{
	int size = strlen(msg);
	if(size <= 0){
		return;
	}
	int msgPos = -1;
	int msgSize = std::stoi(extractWord(msg, msgPos));

	Message message(new String(&msg[msgPos], msgSize));
	messages.push_back(message);

	if(msgPos+msgSize < size){
		processMessage(&msg[msgPos + msgSize]);
	}
}


void TransportLayer::clear()
{
	messages.clear();
}

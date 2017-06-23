#include <cstring>

#include "TransportLayer.hpp"



TransportLayer::Iterator TransportLayer::begin()
{
	return Iterator(messages_.begin()); 
}

TransportLayer::Iterator TransportLayer::end()
{ 
	return Iterator(messages_.end()); 
}


void TransportLayer::processMessage()
{
	processMessageHelper(buffer);
}


void TransportLayer::processMessageHelper(char* msg)
{
	int size = strlen(msg);
	if(size <= 0){
		return;
	}
	int msgPos = -1;
	int msgSize = std::stoi(wordExtractor_(msg, msgPos));

	Message message_(new String(&msg[msgPos], msgSize));
	messages_.push_back(message_);

	if(msgPos+msgSize < size){
		processMessageHelper(&msg[msgPos + msgSize]);
	}
}

void TransportLayer::clear()
{
	messages_.clear();
}

size_t TransportLayer::getBufferSize() const
{
	return bufferSize; 
}

char* TransportLayer::getBuffer() 
{
	return buffer; 
}

void TransportLayer::setEnd(const int sz, const char c) 
{
	buffer[sz] = c; 
}

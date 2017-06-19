#ifndef CONVERSATION_HPP
#define CONVERSATION_hpp

#include <string>
#include <list>
#include <memory>

class Conversation
{
public:
	using String = std::string;
	using SizeType = String::size_type;
	using Conv = std::list<String>;
	using ConvPtr = std::shared_ptr<Conv>;

	Conversation() = delete;
	Conversation(const String&, const String&);

	bool equal(const String& u1, const String& u2) const;

	void addMessage(const String& msg);

	ConvPtr getConversation();
	
private:
	String fileName;
};

#endif

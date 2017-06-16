#ifndef CONVERSATION_HPP
#define CONVERSATION_hpp

#include <string>

class Conversation
{
public:
	using String = std::string;
	using SizeType = String::size_type;

	Conversation() = delete;

	Conversation(const String&, const String&);

	bool equal(const String& u1, const String& u2) const;

	void addMessage(const String& msg);

private:
	String fileName;
};

#endif

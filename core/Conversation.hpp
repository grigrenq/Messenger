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
	Conversation(const String&);
	Conversation(const String&, const String&);
	Conversation(const Conversation&);

	bool equal(const String&, const String&) const;

	void addMessage(const String&);

	ConvPtr getConversation();
	String getFileName() const;
	
public:
	String fileName_;
};

#endif

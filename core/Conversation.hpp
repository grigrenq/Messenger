#ifndef CONVERSATION_HPP
#define CONVERSATION_hpp

#include <string>
#include <list>
#include <memory>
#include <mutex>

#include <boost/thread/shared_mutex.hpp>

class Conversation
{
public:
	using String = std::string;
	using SizeType = String::size_type;
	using Conv = std::list<String>;
	using ConvPtr = std::shared_ptr<Conv>;
	using lockGuard = std::lock_guard<boost::shared_mutex>;
	using shLockGuard = boost::shared_lock<boost::shared_mutex>;

	Conversation() = delete;
	Conversation(const String&);
	Conversation(const String&, const String&);
	Conversation(const Conversation&);

	bool equal(const String&, const String&) const;

	void addMessage(const String&);

	ConvPtr getConversation() const;
	String getFileName() const;
	
public:
	String fileName_;
	mutable boost::shared_mutex mutex_;
};

#endif

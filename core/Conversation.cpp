#include "Conversation.hpp"

#include "Files.hpp" 
#include <fstream>



Conversation::Conversation(const String& n)
: fileName_(n)
{
	//
}

Conversation::Conversation(const String& u1, const String& u2)
: fileName_(u1 + u2)
{
	//
}

Conversation::Conversation(const Conversation& c)
: fileName_(c.fileName_)
{
	//
}

bool Conversation::equal(const String& u1, const String& u2) const
{
	if (u1 == u2) {
		if (fileName_ == u1 + u2) {
			return true;
		} else {
			return false;
		}
	}

	String s1 = u1 + u2;
	String s2 = u2 + u1;
	if (fileName_ == s1 || fileName_ == s2) {
		return true;
	} else {
		return false;
	}
}

void Conversation::addMessage(const String& msg)
{
	String file = Files::convDir + fileName_ + Files::fileType;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(msg.c_str(), msg.size());
	ofile.write("\n", 1);
	ofile.close();
}

#include <iostream>

Conversation::ConvPtr Conversation::getConversation()
{
	std::cout << "Conversation::getConversation()\n";
	ConvPtr p(new Conv);
	String file = Files::convDir + fileName_ + Files::fileType;
	std::ifstream ifile(file, std::fstream::in);
	String s;
	while (std::getline(ifile, s)) {
		p->push_back(s);
	}
	return p;
}


Conversation::String Conversation::getFileName() const
{
	return fileName_;
}

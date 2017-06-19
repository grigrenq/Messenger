#include "Conversation.hpp"

#include "Files.hpp" 
#include <fstream>


Conversation::Conversation(const String& u1, const String& u2)
: fileName(u1 + u2)
{
	//
}


bool Conversation::equal(const String& u1, const String& u2) const
{
	SizeType sz = fileName.find(u1);
	if (sz == String::npos) {
		return false;
	} else {
		sz = fileName.find(u2);
	}
	if (sz == String::npos) {
		return false;
	} else {
		return true;
	}
}

void Conversation::addMessage(const String& msg)
{
	String file = Files::ConvDir + fileName + Files::fileType;
	std::ofstream ofile(file, std::fstream::out | std::fstream::app);
	ofile.write(msg.c_str(), msg.size());
	ofile.write("\n", 1);
	ofile.close();
}

Conversation::ConvPtr Conversation::getConversation()
{
	ConvPtr p(new Conv);
	String file = Files::ConvDir + fileName + Files::fileType;
	std::ifstream ifile(file, std::fstream::in);
	String s;
	while (std::getline(ifile, s)) {
		p->push_back(s);
	}
	return p;
}

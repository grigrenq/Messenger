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
	std::ofstream ofile(Files::ConvDir + fileName, std::fstream::out | std::fstream::app);
	ofile.write(msg.c_str(), msg.size());
	ofile.write("\n", 1);
	ofile.close();
}

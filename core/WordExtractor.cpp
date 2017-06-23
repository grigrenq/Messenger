#include "WordExtractor.hpp"

#include <sstream>
#include <cstring>


WordExtractor::String WordExtractor::operator()(String& str, const bool erase, const char d)
{
	std::stringstream ss(str);
	String word;
	std::getline(ss, word, d);
	if (erase == true) {
		str.erase(str.find(word), word.size() + 1);
	}
	return word;
}

WordExtractor::String WordExtractor::operator()(char* msg,int &divPos)
{
	divPos = static_cast<char*>(memchr(msg, delim, std::strlen(msg))) - msg + 1;
	
	return String(msg, divPos);
}



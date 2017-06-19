#include "ExtractWord.hpp"

#include <sstream>

std::string ExtractWord::operator()(std::string& str, const bool erase, const char d)
{
	std::stringstream ss(str);
	std::string word;
	std::getline(ss, word, d);
	if (erase == true) {
		str.erase(str.find(word), word.size() + 1);
	}
	return word;
}

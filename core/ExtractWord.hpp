#ifndef EXTRACTWORD_HPP
#define EXTRACTWORD_HPP

extern const char delim;

#include <sstream>
#include <string>


struct ExtractWord : std::binary_function<std::string&, const bool, std::string>
{
	std::string operator()(std::string& str, const bool erase = true, const char d = delim)
	{
		std::stringstream ss(str);
		std::string word;
		std::getline(ss, word, d);
		if (erase ==true) {
			str.erase(str.find(word), word.size() + 1);
		}
		return word;
	}
};


#endif

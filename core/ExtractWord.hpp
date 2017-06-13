#ifndef EXTRACTWORD_HPP
#define EXTRACTWORD_HPP

extern const char delim;

#include <sstream>
#include <string>


struct ExtractWord : std::binary_function<std::string&, const char, std::string>
{
	std::string operator()(std::string& str, const char d = delim)
	{
		std::stringstream ss(str);
		std::string word;
		std::getline(ss, word, d);
		str.erase(str.find(word), word.size() + 1);

		return word;
	}
};


#endif

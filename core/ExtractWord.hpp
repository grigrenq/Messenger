#ifndef EXTRACTWORD_HPP
#define EXTRACTWORD_HPP

//extern const char delim;

#include <string>


struct ExtractWord : std::binary_function<std::string&, const bool, std::string>
{
	static const char delim = '%';
	std::string operator()(std::string& str, const bool erase = true, const char d = delim);
};


#endif

#ifndef WORDEXTRACTOR_HPP
#define WORDEXTRACTOR_HPP

#include <string>


struct WordExtractor : std::binary_function<std::string&, const bool, std::string>
{
	using String = std::string;

	static const char delim = '%';

	String operator()(String& str, const bool erase = true, const char d = delim);

	String operator()(char*, int&);
};


#endif

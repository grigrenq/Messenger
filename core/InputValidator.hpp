#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP

#include "ValidationInfo.hpp"

#include <string>

class InputValidator
{
public:
	using String = std::string;
	using SizeType = String::size_type;

	String checkLogin(const String& s) const;
	String checkPassword(const String& s) const;
	String checkName(const String& s) const;
	String checkSurName(const String& s) const;
	bool checkPasswords(const String& p1, const String& p2) const;

private:
	bool checkIsNotAlpha(const String& s) const;
	bool checkIsAlNum(const String& s) const;
};

#endif

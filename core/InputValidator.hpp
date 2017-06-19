#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP

#include "ValidationInfo.hpp"

class InputValidator
{
    public:
        using String = std::string;
        using SizeType = std::string::size_type;
    
    private:
        bool checkIsNotAlpha(const String& s) const
        bool checkIsAlNum(Const String& s) const

    public:
        bool checkLogin(const String& s) const
        bool checkPassword(const String& s) const
        String checkName(const String& s) const
        String checkSurname(const String& s) const
        bool checkPasswords(const String& p1, const String& p2) const
};

#endif

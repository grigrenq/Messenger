#include "InputValidator.hpp"
#include <iostream>
using String = InputValidator::String;

bool InputValidator::checkIsNotAlpha(const String& s) const
{
    const SizeType sz = s.size();
    for (SizeType i = 0; i < sz; ++i) {
        if (!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

bool InputValidator::checkIsAlNum(const String& s) const
{
    const SizeType sz = s.size();
    for (SizeType i = 0; i < sz; ++i) {
        if (!isalnum(s[i]) && s[i] != ValidationInfo::underscore) {
            return false;
        }
    }
    return true;

}


String InputValidator::checkLogin(const String& s) const
{
    const SizeType sz = s.size();
    if(sz == 0){
        return ValidationInfo::emptyField;
    }
    if (checkIsAlNum(s) && sz <= ValidationInfo::maximumSymbols && sz >= ValidationInfo::minimalSymbols) {
        return ValidationInfo::validLog;
    } else if(sz > ValidationInfo::maximumSymbols){
        return ValidationInfo::validMaxLength;
    } else if(sz < ValidationInfo::minimalSymbols){
        return ValidationInfo::validMinLength;
    } else {
        return ValidationInfo::invalidSymbol;
    }
}

String InputValidator::checkPassword(const String& s) const
{
    return checkLogin(s);
}

String InputValidator::checkName(const String& s) const
{
    const SizeType sz = s.size();
    if(sz == 0){
        return ValidationInfo::emptyField;
    }
    if(checkIsNotAlpha(s) && sz <= ValidationInfo::maximumSymbols && sz >= ValidationInfo::minimalSymbols){
        return ValidationInfo::validName;
    } else if (sz > ValidationInfo::maximumSymbols) {
        return ValidationInfo::validMaxLength;
    } else if (sz < ValidationInfo::minimalSymbols) {
        return ValidationInfo::validMinLength;
    } else { 
        return ValidationInfo::invalidSymbol;
    }
}

String InputValidator::checkSurName(const String& s) const
{
    return checkName(s);
}

bool InputValidator::checkPasswords(const String& p1, const String& p2) const
{
    if(p1 == p2){
        return true;
    }
    return false;
}

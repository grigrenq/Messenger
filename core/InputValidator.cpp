#include "InputValidator.hpp"

bool InputValidator::checkIsNotAlpha(const String& s) const
{
    const Sizetype sz = s.szie();
    for (SizeType i = 0; i < sz; ++i) {
        if (!isalpha(s[i])) {
            return true;
        }
    }
    return false;
}

bool InputValidator::checkIsAlNum(const String& s) const
{
    for (SizeType i = 0; i < sz; ++i) {
        if (!isalnum(s[i]) && s[i] != ValidationInfo::underscore) {
            return true;
        }
    }
    return false;

}


bool InputValidator::checkLogin(const String& s) const
{
    const SizeType sz = s.size();
    if (checkIsAlNum(s) && sz > ValidationInfo::maximumSymbols && sz < ValidationInfo::minimalSymbols) {
        return true;
    }
    return false;
}

bool InputValidator::checkPassword(const String& s) const
{
    return checkLogin(s);
}

String InputValidator::checkName(const String& s) const
{
    const SizeType sz = s.size();
    if(checkIsNotAlpha(s) && sz < ValidationInfo::maximumSymbols && sz > ValidationInfo::validMinLength){
        return "";
    } else if (sz > ValidationInfo::maximumSymbols) {
        return ValidationInfo::validMaxLength;
    } else if (sz < ValidationInfo::minimalSymbols) {
        return ValidationInfo::validMinLength;
    } else 
        return "isNotAlpha";
}

String InputValidator::checkSurName(const String& s) const
{
    return checkName(s);
}

bool InputValidator::checkPasswords(const String& p1, const String& p2)
{
    if(p1 != p2){
        return true;
    }
    return false;
}

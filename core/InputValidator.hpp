#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP

#include "ValidationInfo.hpp"

class InputValidator
{
	public:
		using String = std::string;
		using SizeType = std::string::size_type;

		String checkLoginPassword(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz > ValidationInfo::maximumSymbols) {
				return ValidationInfo::validMaxLength;
			}
            if (sz < ValidationInfo::minimalSymbols) {
                return ValidationInfo::validMinLength;
            }
			for (SizeType i = 0; i < sz; ++i) {
					if (!isalnum(s[i]) && s[i] != ValidationInfo::underscore) {
						return ValidationInfo::validLogPass;
				}
			}
			return "";
		}

		String checkName(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz > ValidationInfo::maximumSymbols) {
				return ValidationInfo::validMaxLength;
			}
            if (sz < ValidationInfo::minimalSymbols) {
                return ValidationInfo::validMinLength;
            }
			for (SizeType i = 0; i < sz; ++i) {
				if (!isalpha(s[i])) {
					return ValidationInfo::validName;
				}
			}
			return "";
		}

		String checkPasswords(const String& p1, const String& p2) const
		{
            if (p1 != p2) {
                return ValidationInfo::mismatchPass;
            }
			return "";
		}
};

#endif

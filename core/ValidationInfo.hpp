#ifndef VALIDATIONINFO_HPP
#define VALIDATIONINFO_HPP

namespace ValidationInfo
{
    using String = std::string;
	using SizeType = String::size_type;
    
    const SizeType minimalSymbols = 2;
    const SizeType maximumSymbols = 20;
    const char underscore = '_';

    const String emptyField = "Empty field.";
    const String loggedUser = "Logged user";
    const String validLogPass = "Valid log pass";
    const String validAccount = "Valid account";
    const String validMaxLength = "Valid max length";
    const String validMinLength = "Valid min length";
    const String validName = "Valid name";
    const String takenLogin = "Taken login";
    const String mismatchPass = "Mismatching pass";
};
#endif



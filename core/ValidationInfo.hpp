#ifndef VALIDATIONINFO_HPP
#define VALIDATIONINFO_HPP
#include <string>

namespace ValidationInfo
{
    using String = std::string;
	using SizeType = std::string::size_type;
    
    const SizeType minimalSymbols = 2;
    const SizeType maximumSymbols = 20;
    const char underscore = '_';

    const String emptyField = "Emptyfield.";
    const String loggedUser = "Loggeduser";
    const String validLogPass = "Validlogpass";
    const String validAccount = "Validaccount";
    const String validMaxLength = "Validmaxlength";
    const String validMinLength = "Validminlength";
    const String validName = "Validname";
    const String takenLogin = "Takenlogin";
    const String mismatchPass = "Mismatchingpass";
};

#endif



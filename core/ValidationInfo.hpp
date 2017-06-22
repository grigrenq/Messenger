#ifndef VALIDATIONINFO_HPP
#define VALIDATIONINFO_HPP

#include <string>


namespace ValidationInfo
{
    using String = std::string;
	using SizeType = String::size_type;
    
    const SizeType minimalSymbols = 3;
    const SizeType maximumSymbols = 20;
    const char underscore = '_';

    const String invalidSymbol = "invalidSymbol";
    const String emptyField = "Emptyfield.";
    const String loggedUser = "Loggeduser";
    const String validLog = "Validlog";
    const String validPass = "Validpass";
    const String validAccount = "Validaccount";
    const String validMaxLength = "Validmaxlength";
    const String validMinLength = "Validminlength";
    const String validName = "Validname";
    const String takenLogin = "Takenlogin";
    const String mismatchPass = "Mismatchingpass";
};

#endif



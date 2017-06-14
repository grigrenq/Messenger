#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP

//extern const char underscore;

class InputValidator
{
	public:
		typedef std::string String;
		typedef std::string::size_type SizeType;

		InputValidator()
			: minimalSymbols(4), maximumSymbols(20)
		{
		}

		bool checkLoginPassword(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz > maximumSymbols || sz < minimalSymbols) {
				return false;
			}
			for (SizeType i = 0; i < sz; ++i) {
					if (!isalnum(s[i]) && s[i] != underscore) {
						return false;
				}
			}
			return true;
		}

		bool checkName(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz > maximumSymbols || sz < minimalSymbols) {
				return false;
			}
			for (SizeType i = 0; i < sz; ++i) {
				if (!isalpha(s[i])) {
					return false;
				}
			}
			return true;
		}

		bool checkPasswords(const String& p1, const String& p2) const
		{
			return p1 == p2;
		}
	private:
		const SizeType minimalSymbols;
		const SizeType maximumSymbols;
		const char underscore = '_';
};

#endif

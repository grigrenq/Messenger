
#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP


class InputValidator
{
	public:
		using SizeType = size_t;
		using String = std::string;

		bool checkLoginOrPassword(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz > maximumSymbols || sz < minimalSymbols) {
				return false;
			}
			for (auto i = 0; i < sz; ++i) {
					if (!isalnum(s[i]) && s[i] != underscore) {
						return false;
				}
			}
			return true;
		}

		bool checkName(const String& s) const
		{
			const SizeType sz = s.size();
			if (sz < maximumSymbols || sz < minimalSymbols) {
				return false;
			}
			for (auto i = 0; i < sz; ++i) {
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
		const SizeType minimalSymbols = 5;
		const SizeType maximumSymbols = 12;
};

#endif

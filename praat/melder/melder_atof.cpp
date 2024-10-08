/* melder_atof.cpp
 *
 * Copyright (C) 2003-2008,2011,2015-2019,2021,2023 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "melder.h"

#include <iostream>
#include <locale>

namespace {

struct array_istreambuf : public std::streambuf {
	explicit array_istreambuf(const char *in, const char *end) {
		auto ccin = const_cast<char *>(in);
		auto ccend = const_cast<char *>(end);
		setg(ccin, ccin, ccend);
	}

	using std::streambuf::gptr;
};

double strtod_c(const char *s, const char *r, char **e) {
	static auto cLocale = std::locale::classic();
	static auto &cNumget = std::use_facet<std::num_get<char>>(cLocale);
	static auto &cCtype = std::use_facet<std::ctype<char>>(cLocale);
	static std::ios format(nullptr);  // Wake me up when Praat gets thread-safe. But I'd hope that that global array of buffers will also have changed by then.
	std::ios_base::iostate err = std::ios_base::goodbit;

	const char *p = s;
	while (cCtype.is(std::ctype_base::space, *p)) ++p;

	array_istreambuf buffer(p, r);
	double value = 0.0;
	cNumget.get(&buffer, nullptr, format, err, value);

	if (e) *e = ((err & ~std::ios_base::eofbit) == std::ios_base::goodbit ? buffer.gptr() : const_cast<char *>(s));
	return value;
}

}

/**
	Assume that the next thing that follows is a numeric string,
	and find the end of it.
	Return null on error.
*/
template <typename T>
static const T *findEndOfNumericString (const T *string) {
	const T *p = & string [0];
	/*
		Leading white space is OK.
	*/
	while (Melder_isAsciiHorizontalOrVerticalSpace (*p))
		p ++;
	/*
		Next we accept an optional leading plus or minus.
	*/
	if (*p == '+' || *p == '-')
		p ++;
	/*
		The next character has to be a decimal digit.
		So we don't allow things like ".5".
	*/
	if (! Melder_isAsciiDecimalNumber (*p))
		return nullptr;   // string is not numeric
	/*
		Special case: hexadecimal numbers.
	*/
	if (*p == '0' && (p [1] == 'x' || p [1] == 'X')) {
		p += 2;
		while (Melder_isHexadecimalDigit (*p))
			p ++;
		if (*p == '.')
			p ++;
		while (Melder_isHexadecimalDigit (*p))
			p ++;
		if (*p == 'p' || *p == 'P')
			p ++;
		if (*p == '+' || *p == '-')
			p ++;
		while (Melder_isAsciiDecimalNumber (*p))   // not hexadecimal!
			p ++;
		return p;
	}
	p ++;
	/*
		Then we accept any number of decimal digits.
	*/
	while (Melder_isAsciiDecimalNumber (*p))
		p ++;
	/*
		Next we accept an optional decimal point.
	*/
	if (*p == '.') {
		p ++;
		/*
			We accept any number of (even zero) decimal digits after the decimal point.
		*/
		while (Melder_isAsciiDecimalNumber (*p))
			p ++;
	}
	// Next we accept an optional exponential E or e.
	if (*p == 'e' || *p == 'E') {
		p ++;
		/*
			In the exponent we accept an optional leading plus or minus.
		*/
		if (*p == '+' || *p == '-')
			p ++;
		/*
			The exponent shall contain at least one decimal digit.
			So we don't allow things like "+2.1E".
		*/
		if (! Melder_isAsciiDecimalNumber (*p))
			return nullptr;   // string is not numeric
		p ++;   // skip first decimal digit
		/*
			Then we accept any number of decimal digits.
		*/
		while (Melder_isAsciiDecimalNumber (*p))
			p ++;
	}
	/*
		Next we accept an optional percent sign.
	*/
	if (*p == '%')
		p ++;
	/*
		We have found the end of the numeric string.
	*/
	return p;
}

bool Melder_isStringNumeric (conststring32 string) {
	if (! string)
		return false;
	const char32 *p = findEndOfNumericString (string);
	bool weFoundANumber = !! p;
	if (! weFoundANumber)
		return false;
	Melder_skipHorizontalOrVerticalSpace (& p);
	bool contentFollowsTheNumber = ( *p != U'\0' );
	if (contentFollowsTheNumber)
		return false;
	return true;
}

double Melder8_strtod(const char *str, char **end_str /*= nullptr*/) {
	// findEndOfNumericString(str) because https://bugs.llvm.org/show_bug.cgi?id=17782
	// See https://github.com/tardate/LittleCodingKata/blob/master/cpp/DoubleTrouble/README.md
	return strtod_c(str, findEndOfNumericString(str), end_str);
}

double Melder_a8tof (conststring8 string) {
	if (! string)
		return undefined;
	const char *p = findEndOfNumericString (string);
	const bool weFoundANumber = !! p;
	if (! weFoundANumber)
		return undefined;
	Melder_assert (p - & string [0] > 0);
	return p [-1] == '%' ? 0.01 * strtod_c (string, p, nullptr) : strtod_c (string, p, nullptr);
}

double Melder_atof (conststring32 string) {
	if (! string)
		return undefined;
	const char32 *endOfNumericString = findEndOfNumericString (string);
	const bool weFoundANumber = !! endOfNumericString;
	if (! weFoundANumber)
		return undefined;
	const integer numberOfCharacters = endOfNumericString - & string [0];
	Melder_assert (numberOfCharacters > 0);
	static MelderString buffer;
	MelderString_ncopy (& buffer, string, numberOfCharacters);
	const char *string8 = Melder_peek32to8 (buffer.string);
	const integer string8length = Melder8_length (string8);
	if (string8length < 1)
		return undefined;
	return string8 [string8length - 1] == '%' ? 0.01 * strtod (string8, nullptr) : strtod (string8, nullptr);
}

int64 Melder_atoi (conststring32 string) {
	return strtoll (Melder_peek32to8 (string), nullptr, 10);
}

/* End of file melder_atof.cpp */

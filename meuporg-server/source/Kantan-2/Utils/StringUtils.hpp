#ifndef KANTAN_STRINGUTILS
#define KANTAN_STRINGUTILS

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace kantan
{
	// Convert x to std::string.
	template<typename T>
	std::string from(T x);

	// Convert std::string to x.
	template<typename T>
	T to(std::string str);

	// Trim a string.
    std::string trim(std::string s);

	#include "StringUtils.inl"
} // namespace kantan.

#endif // KANTAN_STRINGUTILS

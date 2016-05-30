#ifndef KANTAN_STRINGUTILS
#define KANTAN_STRINGUTILS

#include <iostream>
#include <fstream>
#include <sstream>

namespace kantan
{
	// Convert x to std::string.
	template<typename T>
	std::string from(T x);

	// Convert std::string to x.
	template<typename T>
	T to(std::string str);

	#include "StringUtils.inl"
} // namespace kantan.

#endif // KANTAN_STRINGUTILS

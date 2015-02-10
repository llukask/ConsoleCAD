#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>

template<class T> T fromString(std::string& s) {
	std::istringstream stream(s);
	T t;
	stream >> t;
	return t;
}

#endif
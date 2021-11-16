#pragma once
#include <ostream>

inline void printArray(std::ostream & out, const auto & array) {
	bool first = true;
	for(const auto & element : array) {
		if(first) first = false;
		else {
			out << ", ";
		}
		out << element;
	}
}
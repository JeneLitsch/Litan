#pragma once
#include <vector>

template<class T>
inline std::vector<T> operator+(
	const std::vector<T> & vecL,
	const std::vector<T> & vecR) {
	std::vector<T> vec = {};
	// vec.reserve(vecL.size() + vecR.size());
	std::copy(vecL.begin(), vecL.end(), std::back_inserter(vec));
	std::copy(vecR.begin(), vecR.end(), std::back_inserter(vec));
	return vec;
}
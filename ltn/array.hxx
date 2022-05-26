#pragma once
#include <array>

template<typename T, std::size_t SIZE>
constexpr inline std::array<T, SIZE + 1> appended(
	const std::array<T, SIZE> & l,
	const T & r) {
	std::array<T, SIZE + 1> arr;
	std::copy_n(l.begin(), SIZE, arr.begin());
	arr.back() = r;
	return arr;
}
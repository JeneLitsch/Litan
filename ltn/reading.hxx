#pragma once

template<typename T>
T read(std::istream & in) {
	T value;
	in >> value;
	return value;
}
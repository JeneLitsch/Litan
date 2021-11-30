#pragma once
#include <cstring>
namespace ltn {
	template<class Dest>
	Dest bitcast(const auto & source) {
		Dest dest;
		std::memcpy(&dest, &source, sizeof(Dest));
		return dest;
	}
}
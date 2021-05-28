#pragma once

#include <cstdint>
#include <array>

// collection for splitting mergin and converting primitive types
namespace ltn {
	class Float {
	public:
		
		static std::uint64_t doubleToUint(double flt);
		static double uintToDouble(std::uint64_t uInt);
	};
}
#include "LtnFloat.hxx"
#include <limits>
#include <cmath>
#include <iostream>
#include <bitset>

std::uint64_t ltn::Float::doubleToUint(double flt){
	// extract parts
	int exponent;
	const std::uint64_t mantisse = static_cast<std::uint64_t>(std::abs(frexp(flt, &exponent) * std::pow(2, 53)));
	const std::uint64_t negative = flt < 0;

	return 	
		mantisse | 
		static_cast<std::uint64_t>(exponent & 0xff) + 128 << 53 |
		(negative & 0x1) << 63;
}

double ltn::Float::uintToDouble(std::uint64_t uInt){
	const std::uint64_t exponent = static_cast<std::uint64_t>(static_cast<std::int8_t>(uInt >> 53)-128); 
	const bool negative = (uInt) & (UINT64_C(1) << 63);	
	const double fMantisse 
		= static_cast<double>(uInt & 0x1FFFFFFFFFFFFF)
		/ static_cast<double>(UINT64_C(2) << 53);
	const double flt = fMantisse * static_cast<double>(UINT64_C(2) << exponent);
	return (!negative * flt) - (negative * flt);
}
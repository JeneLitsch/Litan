#include "Float.hxx"
#include <limits>
#include <cmath>

std::uint64_t ltn::Float::doubleToUint(double flt){
	// extract parts
	int exponent;
	std::int64_t mantisse = static_cast<std::int64_t>(frexp(flt, &exponent) * std::pow(2, 53));
	bool negative = mantisse < 0;
	
	// trim exponent
	exponent = exponent & 0x7FF;
	
	// absolute mantisse (sign is added separatly)
	mantisse = std::abs(mantisse);

	// stitch together the number
	std::uint64_t binary = 
		static_cast<std::uint64_t>(mantisse) | 
		static_cast<std::uint64_t>(exponent) << 53 |
		static_cast<std::uint64_t>(negative) << 63;


	return binary;
}



double ltn::Float::uintToDouble(std::uint64_t uInt){
	// exract parts
	int exponent = (uInt >> 53) & 0xff; 
	std::int64_t mantisse = uInt & 0x1FFFFFFFFFFFFF; // 53 x "1"
	bool negative = (uInt >> 63) != 0;
	

	// shift and cast mantisse
	double fMantisse = static_cast<double>(mantisse) / std::pow(2, 53);

	// form float
	double flt = fMantisse * std::pow(2, exponent);

	//apply sign
	if(negative) return -flt;
	return flt;
}
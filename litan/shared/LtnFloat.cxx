#include "LtnFloat.hxx"
#include <limits>
#include <cmath>
#include <iostream>
#include <bitset>
#include <numeric>

static_assert(std::numeric_limits<double>::is_iec559, "IEEE754 is requiered");

std::uint64_t ltn::Float::doubleToUint(double flt){
	return *reinterpret_cast<std::uint64_t*>(&flt);
}

double ltn::Float::uintToDouble(std::uint64_t uInt){
	return *reinterpret_cast<double*>(&uInt);
}
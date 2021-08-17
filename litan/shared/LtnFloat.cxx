#include "LtnFloat.hxx"
#include <limits>
#include <cmath>
#include <iostream>
#include <bitset>
#include <numeric>

static_assert(std::numeric_limits<double>::is_iec559, "IEEE754 is requiered");
static_assert(sizeof(std::uint64_t) == sizeof(double), "IEEE754 64-Bit is requiered for double");

std::uint64_t ltn::Float::doubleToUint(double flt){
	return *reinterpret_cast<std::uint64_t*>(&flt);
}

double ltn::Float::uintToDouble(std::uint64_t uInt){
	return *reinterpret_cast<double*>(&uInt);
}
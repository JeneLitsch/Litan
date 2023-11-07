#include "Literal.hxx"

namespace ltn::c::sst {
	Float::Float(stx::float64_t value) 
		: LiteralOf<Float, stx::float64_t>{value} {}

	Integer::Integer(std::bitset<64> value)
		: Integer(static_cast<std::int64_t>(value.to_ullong())) {}
		
	Integer::Integer(std::int64_t value)
		: LiteralOf<Integer, std::int64_t>{value} {}
}
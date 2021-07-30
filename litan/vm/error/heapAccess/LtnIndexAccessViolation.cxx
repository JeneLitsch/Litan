#include "LtnIndexAccessViolation.hxx"

ltn::IndexAccessViolation::IndexAccessViolation(
	std::uint64_t ptr,
	std::uint64_t idx,
	const std::string & type)
:	AccessViolation(
		"Access violation while accessing object of type " + type + " at pointer " + std::to_string(ptr) + " at index " + std::to_string(idx),
		ptr, idx, type) {}
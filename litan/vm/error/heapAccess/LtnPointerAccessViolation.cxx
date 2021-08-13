#include "LtnPointerAccessViolation.hxx"

ltn::vm::PointerAccessViolation::PointerAccessViolation(
	std::uint64_t ptr,
	const std::string & type)
:	AccessViolation(
		"Access violation while accessing object of type " + type + " at pointer " + std::to_string(ptr),
		ptr, 0, type) {}
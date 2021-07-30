#include "LtnPopFromEmpty.hxx"

ltn::PopFromEmpty::PopFromEmpty(std::uint64_t ptr)
	: AccessViolation(
		"Attempt to pop from empty object at ptr: " + std::to_string(ptr),
		ptr, 0, "Buffer") {}
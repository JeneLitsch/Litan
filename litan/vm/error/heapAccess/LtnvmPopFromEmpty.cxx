#include "LtnvmPopFromEmpty.hxx"

ltn::vm::PopFromEmpty::PopFromEmpty(std::uint64_t ptr)
	: AccessViolation(
		"Attempt to pop from empty object at ptr: " + std::to_string(ptr),
		ptr, 0, "Buffer") {}
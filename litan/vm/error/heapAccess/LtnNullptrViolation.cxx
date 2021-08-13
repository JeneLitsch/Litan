#include "LtnNullptrViolation.hxx"

ltn::vm::NullptrViolation::NullptrViolation()
	: AccessViolation("Access violation at null", 0, 0, "nullptr") {}
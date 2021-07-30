#include "LtnNullptrViolation.hxx"

ltn::NullptrViolation::NullptrViolation()
	: AccessViolation("Access violation at null", 0, 0, "nullptr") {}
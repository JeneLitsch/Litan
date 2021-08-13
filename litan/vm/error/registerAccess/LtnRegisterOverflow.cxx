#include "LtnRegisterOverflow.hxx"

ltn::vm::RegisterOverflow::RegisterOverflow()
	: RuntimeError("Register overflow") {}

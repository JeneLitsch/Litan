#include "LtnRegisterUnderflow.hxx"

ltn::vm::RegisterUnderflow::RegisterUnderflow()
	: RuntimeError("Register underflow") {}

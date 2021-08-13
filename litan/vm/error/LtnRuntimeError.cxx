#include "LtnRuntimeError.hxx"

ltn::vm::RuntimeError::RuntimeError(const std::string & msg)
	: Error(msg) {}

ltn::vm::RuntimeError::RuntimeError()
	: Error("An error occured during runtime") {}
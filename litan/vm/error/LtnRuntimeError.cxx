#include "LtnRuntimeError.hxx"

ltn::RuntimeError::RuntimeError(const std::string & msg)
	: Error(msg) {}

ltn::RuntimeError::RuntimeError()
	: Error("An error occured during runtime") {}
#pragma once
#include "LtnvmRuntimeError.hxx"

namespace ltn::vm {
	class RegisterUnderflow : public RuntimeError {
	public:
		RegisterUnderflow();
	};
}
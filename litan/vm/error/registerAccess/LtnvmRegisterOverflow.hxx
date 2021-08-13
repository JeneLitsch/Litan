#pragma once
#include "LtnvmRuntimeError.hxx"

namespace ltn::vm {
	class RegisterOverflow : public RuntimeError {
	public:
		RegisterOverflow();
	};
}
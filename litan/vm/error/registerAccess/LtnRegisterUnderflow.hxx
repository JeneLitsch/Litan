#pragma once
#include "LtnRuntimeError.hxx"

namespace ltn::vm {
	class RegisterUnderflow : public RuntimeError {
	public:
		RegisterUnderflow();
	};
}
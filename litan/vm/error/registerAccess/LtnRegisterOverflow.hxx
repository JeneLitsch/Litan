#pragma once
#include "LtnRuntimeError.hxx"

namespace ltn::vm {
	class RegisterOverflow : public RuntimeError {
	public:
		RegisterOverflow();
	};
}
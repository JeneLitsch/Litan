#pragma once
#include "LtnRuntimeError.hxx"

namespace ltn {
	class RegisterOverflow : public RuntimeError {
	public:
		RegisterOverflow();
	};
}
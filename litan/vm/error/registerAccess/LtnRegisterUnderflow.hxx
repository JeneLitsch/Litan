#pragma once
#include "LtnRuntimeError.hxx"

namespace ltn {
	class RegisterUnderflow : public RuntimeError {
	public:
		RegisterUnderflow();
	};
}
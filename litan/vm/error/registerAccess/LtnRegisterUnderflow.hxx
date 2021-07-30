#pragma once
#include "LtnError.hxx"

namespace ltn {
	class RegisterUnderflow : public Error {
	public:
		RegisterUnderflow();
	};
}
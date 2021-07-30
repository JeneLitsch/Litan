#pragma once
#include "LtnError.hxx"

namespace ltn {
	class RegisterOverflow : public Error {
	public:
		RegisterOverflow();
	};
}
#pragma once
#include "LtnvmAccessViolation.hxx"

namespace ltn::vm {
	class NullptrViolation : public AccessViolation {
	public:
		NullptrViolation();
	};
}
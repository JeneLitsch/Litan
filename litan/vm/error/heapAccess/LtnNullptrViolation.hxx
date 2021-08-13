#pragma once
#include "LtnAccessViolation.hxx"

namespace ltn::vm {
	class NullptrViolation : public AccessViolation {
	public:
		NullptrViolation();
	};
}
#pragma once
#include "LtnAccessViolation.hxx"
namespace ltn {
	class NullptrViolation : public AccessViolation {
	public:
		NullptrViolation();
	};
}
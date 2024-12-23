#pragma once
#include "signatures.hxx"

namespace ltn::c::type {
	struct UnaryOperation {
		std::vector<UnarySignature> signatures;
	};

	struct BinaryOperation {
		std::vector<BinarySignature> signatures;
	};

	extern const BinaryOperation arithmetic;
}

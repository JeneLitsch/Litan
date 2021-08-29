#pragma once
#include "LtnvmAccessViolation.hxx"

namespace ltn::vm {
	class PopFromEmpty : public AccessViolation {
	public:
		PopFromEmpty(std::uint64_t ptr);
	};
}
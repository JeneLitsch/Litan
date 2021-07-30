#pragma once
#include "LtnAccessViolation.hxx"

namespace ltn {
	class PopFromEmpty : public AccessViolation {
	public:
		PopFromEmpty(std::uint64_t ptr);
	};
}
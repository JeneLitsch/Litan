#pragma once
#include "LtnvmAccessViolation.hxx"
namespace ltn::vm {
	class IndexAccessViolation : public AccessViolation {
	public:
		IndexAccessViolation(
			std::uint64_t ptr,
			std::uint64_t idx,
			const std::string & type);
	};
}
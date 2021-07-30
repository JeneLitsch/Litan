#pragma once
#include "LtnAccessViolation.hxx"
namespace ltn {
	class IndexAccessViolation : public AccessViolation {
	public:
		IndexAccessViolation(
			std::uint64_t ptr,
			std::uint64_t idx,
			const std::string & type);
	};
}
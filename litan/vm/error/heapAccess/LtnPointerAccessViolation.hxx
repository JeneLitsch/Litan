#pragma once
#include "LtnAccessViolation.hxx"
namespace ltn::vm {
	class PointerAccessViolation : public AccessViolation {
	public:
		PointerAccessViolation(
			std::uint64_t ptr,
			const std::string & type);
	};
}

#include "CompilerInfo.hxx"

namespace ltn::c {

	// creates a jump label
	std::string make_jump_id(const std::string_view name) {
		std::stringstream ss;
		ss << "_" << name << *stx::unique{};
		return ss.str();
	}
}
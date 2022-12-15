#include "make_jump_id.hxx"
#include "ltn/unique.hxx"
#include <sstream>

namespace ltn::c {
	std::string make_jump_id(const std::string_view name) {
		std::stringstream ss;
		ss << "_" << name << *stx::unique{};
		return ss.str();
	}
}
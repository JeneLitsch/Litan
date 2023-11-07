#include "Var.hxx"

namespace ltn::c::sst {
	Var::Var(std::size_t address)
		: address{address} {}


	std::uint64_t Var::alloc() const {
		return 0;
	}
}
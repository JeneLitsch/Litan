#include "GlobalVar.hxx"

namespace ltn::c::sst {
	GlobalVar::GlobalVar(std::size_t address)
		: address { address } {}



	std::uint64_t GlobalVar::alloc() const {
		return 0;
	}
}
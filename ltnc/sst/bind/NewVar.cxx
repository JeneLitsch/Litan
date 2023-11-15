#include "NewVar.hxx"

namespace ltn::c::sst::bind {
	NewVar::NewVar(std::uint64_t address)
		: address{std::move(address)} {}



	std::size_t NewVar::alloc_count() const {
		return 1;
	}



	std::unique_ptr<NewVar> new_local(std::uint64_t address) {
		return std::make_unique<NewVar>(address);
	}
}

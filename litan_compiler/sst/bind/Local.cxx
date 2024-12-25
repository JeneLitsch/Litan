#include "Local.hxx"

namespace ltn::c::sst::bind {
	Local::Local(std::uint64_t address)
		: address{address} {}



	std::size_t Local::alloc_count() const { 
		return 0;
	}



	std::unique_ptr<Local> local(std::uint64_t address) {
		return std::make_unique<Local>(address);
	}
}

#include "Global.hxx"

namespace ltn::c::sst::bind {
	Global::Global(std::uint64_t address) 
		: address{address} {}



	std::size_t Global::alloc_count() const { 
		return 0;
	}



	std::unique_ptr<Global> global(std::uint64_t address) {
		return std::make_unique<Global>(address);
	}
};

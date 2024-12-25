#include "Discard.hxx"

namespace ltn::c::sst::bind {
	Discard::Discard() {}
	


	std::size_t Discard::alloc_count() const {
		return 0;
	}



	std::unique_ptr<Discard> discard() {
		return std::make_unique<Discard>();
	}
}

#include "BuildIn.hxx"

namespace ltn::c::sst {
	BuildIn::BuildIn(std::string key)
		: key{std::move(key)} {}

		

	std::uint64_t BuildIn::alloc() const {
		return 0;
	}
}
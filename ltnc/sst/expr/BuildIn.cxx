#include "BuildIn.hxx"

namespace ltn::c::sst {
	BuildIn::BuildIn(std::string key)
		: key{std::move(key)} {}

		

	std::uint64_t BuildIn::alloc() const {
		return 0;
	}



	std::unique_ptr<BuildIn> build_in(std::string key) {
		return std::make_unique<BuildIn>(std::move(key));
	}
}
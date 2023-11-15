#include "Group.hxx"

namespace ltn::c::sst::bind {
	Group::Group() {}



	std::size_t Group::alloc_count() const {
		return std::accumulate(
			std::begin(this->sub_bindings),
			std::end(this->sub_bindings),
			std::size_t{0},
			[] (const auto & curr, const bind_ptr & bind){
				return curr + bind->alloc_count();
			}
		);		
	}



	std::unique_ptr<Group> group() {
		return std::make_unique<Group>();
	}
}

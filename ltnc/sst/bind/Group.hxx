#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Group : public BindingCRTP<Group> {
		Group();
		virtual std::size_t alloc_count() const override;

		std::vector<bind_ptr> sub_bindings;
	};



	std::unique_ptr<Group> group();
}

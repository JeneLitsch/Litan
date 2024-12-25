#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Discard : public BindingCRTP<Discard> {
		Discard();
		virtual std::size_t alloc_count() const override;
	};



	std::unique_ptr<Discard> discard();
}

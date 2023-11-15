#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct NewVar : public BindingCRTP<NewVar> {
		NewVar(std::uint64_t address);
		virtual std::size_t alloc_count() const override;

		std::uint64_t address;
	};

	std::unique_ptr<NewVar> new_local(std::uint64_t address);
}

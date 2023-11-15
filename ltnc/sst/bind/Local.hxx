#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Local final : public BindingCRTP<Local> {
		Local(std::uint64_t address);
		virtual std::size_t alloc_count() const override;

		std::uint64_t address;
	};

	std::unique_ptr<Local> local(std::uint64_t address);
}

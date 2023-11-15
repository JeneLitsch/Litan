#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Global final : public BindingCRTP<Global> {
		Global(std::uint64_t address);
		virtual std::size_t alloc_count() const override;
		std::uint64_t address;
	};



	std::unique_ptr<Global> global(std::uint64_t address);
}

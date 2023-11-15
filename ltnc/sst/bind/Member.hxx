#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Member final : public BindingCRTP<Member> {
		Member(expr_ptr object, std::uint64_t address);
		virtual std::size_t alloc_count() const override;
		virtual ~Member();

		expr_ptr object;
		std::uint64_t address;
	};

	std::unique_ptr<Member> member(expr_ptr object, std::uint64_t id);
}

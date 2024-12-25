#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct Member final : public ExpressionCRTP<Member> {
		Member(expr_ptr expr, std::size_t address);

		virtual std::uint64_t alloc() const override;
		virtual bind_ptr convert_to_bindung() && override;

		expr_ptr expr;
		std::size_t address;
	};



	std::unique_ptr<Member> member(expr_ptr expr, std::uint64_t member);
}
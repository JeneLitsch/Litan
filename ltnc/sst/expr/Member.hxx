#pragma once
#include "Expression.hxx"

namespace ltn::c::sst {
	struct Member final : public ExpressionCRTP<Member> {
		Member(expr_ptr expr, std::size_t address);

		virtual std::uint64_t alloc() const override;

		expr_ptr expr;
		std::size_t address;
	};
}
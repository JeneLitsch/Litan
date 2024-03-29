#pragma once
#include <vector>
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct InvokeMember final : public ExpressionCRTP<InvokeMember> {
		InvokeMember(
			expr_ptr object,
			std::uint64_t member_id,
			std::vector<expr_ptr> arguments);

		virtual std::uint64_t alloc() const override;

		std::uint64_t arity() const;

		expr_ptr object;
		std::uint64_t member_id;
		std::vector<expr_ptr> arguments;
	};

	std::unique_ptr<InvokeMember> invoke_member(expr_ptr object, std::uint64_t member_id, std::vector<expr_ptr> arguments);
}
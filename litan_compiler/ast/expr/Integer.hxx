#pragma once
#include <bitset>
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Integer final : public Expression {
		Integer(std::int64_t value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		
		std::int64_t value;
	};

	std::unique_ptr<Integer> integer(std::int64_t value, const SourceLocation & location);
	std::unique_ptr<Integer> integer(std::bitset<64> value, const SourceLocation & location);
}
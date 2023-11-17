#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Char final : public Expression {
		Char(std::uint8_t value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		std::uint8_t value;
	};

	std::unique_ptr<Char> character(const SourceLocation & location, std::uint8_t value);
}
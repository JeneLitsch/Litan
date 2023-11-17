#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct String final : public Expression {
		String(const std::string & value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		std::string value;
	};

	std::unique_ptr<String> string(const SourceLocation & location, const std::string & value);
}
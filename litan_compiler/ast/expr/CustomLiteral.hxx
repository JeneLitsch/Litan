#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct CustomLiteral final : Expression {
		CustomLiteral(std::string type, std::string value, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		
		std::string type;
		std::string value;
	};

	std::unique_ptr<CustomLiteral> custom_literal(const SourceLocation & location, std::string type, std::string value);
}
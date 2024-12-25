#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct BuildIn final : Expression {
		BuildIn(std::string key, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;
		
		std::string key;
	};

	std::unique_ptr<BuildIn> build_in(const SourceLocation & location, std::string key);
}
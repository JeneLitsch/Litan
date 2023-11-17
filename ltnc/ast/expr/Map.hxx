#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Map final : public Expression {
		struct Pair {
			ast::expr_ptr key;
			ast::expr_ptr val;
		};

		Map(const SourceLocation & location);
		
		virtual void accept(const ExprVisitor & visitor) const override;

		std::vector<Pair> pairs;
	};


	std::unique_ptr<Map> map(const SourceLocation & location);
}
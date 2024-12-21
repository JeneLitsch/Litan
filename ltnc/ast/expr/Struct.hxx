#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Struct final : public Expression {
		struct Member {
			std::string name;
			expr_ptr expr;
		};

		Struct(const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		std::vector<Member> members;
	};

	std::unique_ptr<Struct> strukt(const SourceLocation & location);
}
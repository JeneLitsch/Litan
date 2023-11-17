#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Member final : public Expression {
		Member(
			expr_ptr expr,
			const std::variant<std::string, MemberCode> & name,
			const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		expr_ptr expr;
		std::variant<std::string, MemberCode> name;
	};

	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, const std::variant<std::string, MemberCode> name);
	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, const std::string & name);
	std::unique_ptr<Member> member(const SourceLocation & location, expr_ptr expr, MemberCode code);
}
#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct InvokeMember final : public Expression {
		InvokeMember(
			expr_ptr object,
			const std::variant<std::string, MemberCode> & name,
			std::vector<expr_ptr> arguments,
			const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		std::uint64_t arity() const;

		expr_ptr object;
		std::variant<std::string, MemberCode> name;
		std::vector<expr_ptr> arguments;
	};



	std::unique_ptr<InvokeMember> invoke_member(
		const SourceLocation & location,
		expr_ptr object,
		const std::variant<std::string, MemberCode> & name,
		std::vector<expr_ptr> arguments
	);
}
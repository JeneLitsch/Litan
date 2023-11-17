#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Var final : public Expression {
		Var(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location);

		virtual void accept(const ExprVisitor & visitor) const override;

		std::string name;
		Namespace namespaze;
	};

	std::unique_ptr<Var> variable(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze
	);
}
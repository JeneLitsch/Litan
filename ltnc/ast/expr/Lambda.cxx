#include "Expression.hxx"
#include "ltnc/ast/decl/Function.hxx"

namespace ltn::c::ast::expr {
	Lambda::Lambda(
		func_ptr fx,
		std::vector<std::unique_ptr<Var>> captures,
		const SourceLocation & location)
		: Expression(location)
		, fx(std::move(fx))
		, captures(std::move(captures)) {}



	void Lambda::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	Lambda::~Lambda() {}
}
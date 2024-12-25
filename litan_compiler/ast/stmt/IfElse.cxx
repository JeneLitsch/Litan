#include "IfElse.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	IfElse::IfElse(
		expr_ptr condition,
		stmt_ptr if_branch,
		stmt_ptr else_branch,
		const SourceLocation & location)
		: Statement(location)
		, condition(std::move(condition))
		, if_branch(std::move(if_branch))
		, else_branch(std::move(else_branch)) {}



	void IfElse::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	IfElse::~IfElse() {}



	std::unique_ptr<IfElse> if_else(
		expr_ptr condition,
		stmt_ptr if_branch,
		stmt_ptr else_branch,
		const SourceLocation & location) {
		
		return std::make_unique<IfElse>(std::move(condition), std::move(if_branch), std::move(else_branch), location);
	}
}
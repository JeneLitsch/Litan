#include "StatementExpression.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	StatementExpression::StatementExpression(expr_ptr expr, const SourceLocation & location)
		: Statement(location)
		, expr(std::move(expr)) {}



	void StatementExpression::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	StatementExpression::~StatementExpression() {}



	std::unique_ptr<StatementExpression> just_an_expr(expr_ptr expr, const SourceLocation & location) {
		return std::make_unique<StatementExpression>(std::move(expr), location);
	}
}
#include "Return.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	Return::Return(expr_ptr expr, const SourceLocation & location)
		: Statement(location)
		, expr(std::move(expr)) {}



	void Return::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Return::~Return() {}



	std::unique_ptr<Return> retvrn(expr_ptr expr, const SourceLocation & location) {
		return std::make_unique<Return>(std::move(expr), location);
	}
}

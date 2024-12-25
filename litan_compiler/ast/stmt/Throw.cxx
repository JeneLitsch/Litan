#include "Throw.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	Throw::Throw(expr_ptr expr, const SourceLocation & location) 
		: Statement(location)
		, expr(std::move(expr)) {}



	void Throw::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Throw::~Throw() {}



	std::unique_ptr<Throw> thr0w(expr_ptr expr, const SourceLocation & location) {
		return std::make_unique<Throw>(std::move(expr), location);
	}
}
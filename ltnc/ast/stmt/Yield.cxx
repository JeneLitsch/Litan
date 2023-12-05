#include "Yield.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	Yield::Yield(expr_ptr expr, const SourceLocation & location)
		: Statement(location)
		, expr(std::move(expr)) {}



	void Yield::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Yield::~Yield() {}



	std::unique_ptr<Yield> yield(expr_ptr expr, const SourceLocation & location) {
		return std::make_unique<Yield>(std::move(expr), location);
	}
}

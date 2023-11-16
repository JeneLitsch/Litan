#include "Assign.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	Assign::Assign(
		expr_ptr l,
		expr_ptr r,
		const SourceLocation & location)
		: Statement(location)
		, l(std::move(l))
		, r(std::move(r)) {}



	void Assign::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Assign::~Assign() {}



	std::unique_ptr<Assign> assign(expr_ptr l, expr_ptr r,	const SourceLocation & location) {
		return std::make_unique<Assign>(std::move(l), std::move(r), location);
	}
}
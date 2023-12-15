#include "ForEach.hxx"
#include "ltnc/ast/expr/Expression.hxx"
#include "ltnc/ast/bind/Binding.hxx"

namespace ltn::c::ast::stmt {
	ForEach::ForEach(bind_ptr bind, expr_ptr expr, stmt_ptr body, const SourceLocation & location)
		: Statement(location)
		, bind(std::move(bind))
		, expr(std::move(expr))
		, body(std::move(body)) {}



	void ForEach::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	ForEach::~ForEach() {}



	std::unique_ptr<ForEach> for_each(bind_ptr bind, expr_ptr expr, stmt_ptr body, const SourceLocation & location) {
		return std::make_unique<ForEach>(std::move(bind), std::move(expr), std::move(body), location);
	}
}
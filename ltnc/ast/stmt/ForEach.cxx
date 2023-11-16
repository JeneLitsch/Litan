#include "ForEach.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	ForEach::ForEach(std::string index_name, expr_ptr expr, stmt_ptr body, const SourceLocation & location)
		: Statement(location)
		, index_name(std::move(index_name))
		, expr(std::move(expr))
		, body(std::move(body)) {}



	void ForEach::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	ForEach::~ForEach() {}



	std::unique_ptr<ForEach> for_each(std::string index_name, expr_ptr expr, stmt_ptr body, const SourceLocation & location) {
		return std::make_unique<ForEach>(std::move(index_name), std::move(expr), std::move(body), location);
	}
}
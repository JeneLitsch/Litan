#include "While.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::stmt {
	While::While(
		expr_ptr condition,
		stmt_ptr body,
		const SourceLocation & location)
		: Statement(location)
		, condition(std::move(condition))
		, body(std::move(body)) {}



	void While::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	While::~While() {}



	std::unique_ptr<While> while_loop(expr_ptr condition, stmt_ptr body, const SourceLocation & location) {
		return std::make_unique<While>(std::move(condition), std::move(body), location);
	}
}
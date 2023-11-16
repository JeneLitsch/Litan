#include "Statement.hxx"
#include "ltnc/ast/bind/Binding.hxx"

namespace ltn::c::ast::stmt {
	NewVar::NewVar(
		bind_ptr binding,
		expr_ptr expr,
		const SourceLocation & location)
			: Statement(location)
			, binding(std::move(binding))
			, expr{std::move(expr)} {}



	void NewVar::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	NewVar::~NewVar() {}
}
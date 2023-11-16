#include "NewVar.hxx"
#include "ltnc/ast/bind/Binding.hxx"
#include "ltnc/ast/expr/Expression.hxx"

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



	std::unique_ptr<NewVar> new_local(
		bind_ptr binding,
		expr_ptr expr,
		const SourceLocation & location) {
		
		return std::make_unique<NewVar>(std::move(binding), std::move(expr), location);
	}
}
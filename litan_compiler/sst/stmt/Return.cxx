#include "Return.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Return::Return(
		expr_ptr expr,
		std::optional<std::string> overide_label)
		: Statement{}
		, expr(std::move(expr))
		, overide_label{overide_label} {}



	std::size_t Return::temporary_alloc() const { 
		return this->expr->alloc();
	}



	std::size_t Return::persistent_alloc() const { 
		return 0;
	}



	void Return::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Return::~Return() {}



	std::unique_ptr<Return> r3turn(expr_ptr expr, std::optional<std::string> overide_label) {
		return std::make_unique<Return>(std::move(expr), std::move(overide_label));
	}
}
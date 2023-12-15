#include "CoReturn.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	CoReturn::CoReturn(expr_ptr expr)
		: Statement{}
		, expr(std::move(expr)) {}



	std::size_t CoReturn::nested_alloc() const { 
		return 0;
	}



	std::size_t CoReturn::direct_alloc() const { 
		return this->expr->alloc();
	}



	void CoReturn::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	CoReturn::~CoReturn() {}



	std::unique_ptr<CoReturn> co_retvrn(expr_ptr expr) {
		return std::make_unique<CoReturn>(std::move(expr));
	}
}
#include "Yield.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Yield::Yield(expr_ptr expr)
		: Statement{}
		, expr(std::move(expr)) {}



	std::size_t Yield::temporary_alloc() const { 
		return 0;
	}



	std::size_t Yield::persistent_alloc() const { 
		return this->expr->alloc();
	}



	void Yield::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Yield::~Yield() {}



	std::unique_ptr<Yield> yield(expr_ptr expr) {
		return std::make_unique<Yield>(std::move(expr));
	}
}
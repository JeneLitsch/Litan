#include "Yield.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Yield::Yield(
		expr_ptr expr,
		std::optional<std::string> overide_label)
		: Statement{}
		, expr(std::move(expr))
		, overide_label{overide_label} {}



	std::size_t Yield::nested_alloc() const { 
		return 0;
	}



	std::size_t Yield::direct_alloc() const { 
		return this->expr->alloc();
	}



	void Yield::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Yield::~Yield() {}



	std::unique_ptr<Yield> yield(expr_ptr expr, std::optional<std::string> overide_label) {
		return std::make_unique<Yield>(std::move(expr), std::move(overide_label));
	}
}
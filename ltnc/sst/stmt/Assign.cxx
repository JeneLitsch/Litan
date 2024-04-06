#include "Assign.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst::stmt {
	Assign::Assign(
		bind_ptr binding,
		expr_ptr expr)
		: Statement{}
		, binding{std::move(binding)}
		, expr(std::move(expr)) {}



	std::size_t Assign::temporary_alloc() const {
		return expr->alloc();
	}



	std::size_t Assign::persistent_alloc() const {
		return this->binding->alloc_count();
	}



	void Assign::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Assign::~Assign() {}



	std::unique_ptr<Assign> assign(bind_ptr bind, expr_ptr expr) {
		return std::make_unique<Assign>(std::move(bind), std::move(expr));
	}
}
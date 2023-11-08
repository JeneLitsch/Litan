#include "Assign.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	Assign::Assign(
		std::unique_ptr<Binding> binding,
		std::unique_ptr<Expression> expr)
		: Statement{}
		, binding{std::move(binding)}
		, expr(std::move(expr)) {}



	std::size_t Assign::nested_alloc() const {
		return 0;
	}



	std::size_t Assign::direct_alloc() const {
		return this->binding->alloc_count() + expr->alloc();
	}



	void Assign::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Assign::~Assign() {}



	std::unique_ptr<Assign> assign(std::unique_ptr<Binding> bind, std::unique_ptr<Expression> expr) {
		return std::make_unique<Assign>(std::move(bind), std::move(expr));
	}
}
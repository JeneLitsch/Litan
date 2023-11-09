#include "Assign.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	Assign::Assign(
		bind_ptr binding,
		std::unique_ptr<expr::Expression> expr)
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



	std::unique_ptr<Assign> assign(bind_ptr bind, std::unique_ptr<expr::Expression> expr) {
		return std::make_unique<Assign>(std::move(bind), std::move(expr));
	}
}
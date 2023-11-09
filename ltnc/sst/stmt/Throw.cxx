#include "Throw.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst {
	Throw::Throw(std::unique_ptr<expr::Expression> expr) 
		: Statement{}
		, expr(std::move(expr)) {}



	std::size_t Throw::nested_alloc() const {
		return 0;
	}
	
	
	
	std::size_t Throw::direct_alloc() const {
		return this->expr->alloc();
	}



	void Throw::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Throw::~Throw() {}



	std::unique_ptr<Throw> thr0w(std::unique_ptr<expr::Expression> expr) {
		return std::make_unique<Throw>(std::move(expr));
	}
}
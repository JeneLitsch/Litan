#include "Return.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	Return::Return(
		std::unique_ptr<expr::Expression> expr,
		std::optional<std::string> overide_label)
		: Statement{}
		, expr(std::move(expr))
		, overide_label{overide_label} {}



	std::size_t Return::nested_alloc() const { 
		return 0;
	}



	std::size_t Return::direct_alloc() const { 
		return this->expr->alloc();
	}



	void Return::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	Return::~Return() {}



	std::unique_ptr<Return> r3turn(std::unique_ptr<expr::Expression> expr, std::optional<std::string> overide_label) {
		return std::make_unique<Return>(std::move(expr), std::move(overide_label));
	}
}
#include "While.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	While::While(
		expr_ptr condition,
		stmt_ptr body)
		: Statement{}
		, condition(std::move(condition))
		, body(std::move(body)) {}



	std::size_t While::nested_alloc() const {
		return body->nested_alloc();
	}
	


	std::size_t While::direct_alloc() const {
		return this->condition->alloc();
	}



	void While::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}


	
	While::~While() {}



	std::unique_ptr<While> wh1le(
		expr_ptr condition,
		stmt_ptr body) {
		
		return std::make_unique<While>(std::move(condition), std::move(body));
	}
}
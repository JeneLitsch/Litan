#include <algorithm>
#include "While.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	While::While(
		expr_ptr condition,
		stmt_ptr body)
		: Statement{}
		, condition(std::move(condition))
		, body(std::move(body)) {}



	std::size_t While::temporary_alloc() const {
		const auto condtion_alloc = this->condition->alloc(); 
		const auto body_alloc = this->body->total_alloc(); 
		return std::max({condtion_alloc, body_alloc});
	}
	


	std::size_t While::persistent_alloc() const {
		return 0;
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
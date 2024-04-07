#include "IfElse.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::stmt {
	IfElse::IfElse(
		expr_ptr condition,
		stmt_ptr if_branch,
		stmt_ptr else_branch)
		: Statement{}
		, condition(std::move(condition))
		, if_branch(std::move(if_branch))
		, else_branch(std::move(else_branch)) {}



	std::size_t IfElse::temporary_alloc() const {
		const auto condtion_alloc = this->condition->alloc(); 
		const auto if_alloc = this->if_branch->total_alloc(); 
		const auto else_alloc = this->else_branch ? this->else_branch->total_alloc() : 0; 
		return std::max({condtion_alloc, if_alloc, else_alloc});
	}
	


	std::size_t IfElse::persistent_alloc() const {
		// No persistent allocation
		// No variable in condtion or body leaks to the outside scope 
		return 0;
	}



	void IfElse::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	IfElse::~IfElse() {}



	std::unique_ptr<IfElse> if_else(expr_ptr condition, stmt_ptr if_branch, stmt_ptr else_branch) {
		return std::make_unique<IfElse>(std::move(condition), std::move(if_branch), std::move(else_branch));
	}

	std::unique_ptr<IfElse> if_only(expr_ptr condition, stmt_ptr if_branch) {
		return std::make_unique<IfElse>(std::move(condition), std::move(if_branch), nullptr);
	}
}
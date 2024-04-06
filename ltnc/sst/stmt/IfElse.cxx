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
		return this->else_branch
			? std::max(if_branch->temporary_alloc(), else_branch->temporary_alloc())
			: if_branch->temporary_alloc();
	}
	


	std::size_t IfElse::persistent_alloc() const {
		return this->condition->alloc();
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
#include "IfElse.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst {
	IfElse::IfElse(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> if_branch,
		std::unique_ptr<Statement> else_branch)
		: Statement{}
		, condition(std::move(condition))
		, if_branch(std::move(if_branch))
		, else_branch(std::move(else_branch)) {}



	std::size_t IfElse::nested_alloc() const {
		return this->else_branch
			? std::max(if_branch->nested_alloc(), else_branch->nested_alloc())
			: if_branch->nested_alloc();
	}
	


	std::size_t IfElse::direct_alloc() const {
		return this->condition->alloc();
	}



	void IfElse::accept(const StmtVisitor & visitor) const {
		visitor.visit(*this);
	}



	IfElse::~IfElse() {}



	std::unique_ptr<IfElse> if_else(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> if_branch, std::unique_ptr<Statement> else_branch) {
		return std::make_unique<IfElse>(std::move(condition), std::move(if_branch), std::move(else_branch));
	}
}
#include "Unary.hxx"

namespace ltn::c::sst {
	Unary::Unary(Op op, expr_ptr expr)
		: op(op)
		, expr(std::move(expr)) {}



	std::uint64_t Unary::alloc() const {
		return this->expr->alloc();
	}


	std::unique_ptr<Unary> unary(Unary::Op op, expr_ptr expr) {
		return std::make_unique<Unary>(op, std::move(expr));
	}
}
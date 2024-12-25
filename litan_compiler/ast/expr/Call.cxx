#include "Call.hxx"

namespace ltn::c::ast::expr {
	Call::Call(
		expr_ptr function_ptr,
		std::vector<expr_ptr> arguments,
		const SourceLocation & location)
		: Expression(location)
		, function_ptr(std::move(function_ptr))
		, arguments(std::move(arguments)) {}



	void Call::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::uint64_t Call::arity() const {
		return std::size(this->arguments);
	}



	std::unique_ptr<Call> call(const SourceLocation & location, expr_ptr function_ptr, std::vector<expr_ptr> arguments) {
		return std::make_unique<Call>(std::move(function_ptr), std::move(arguments), location);
	}
}